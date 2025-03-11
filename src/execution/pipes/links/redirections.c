/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 15:27:08 by rguigneb          #+#    #+#             */
/*   Updated: 2025/03/11 15:56:30 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"

static void	link_redirection_to_cmd_node(t_btree_redir_node *redir_node,
		t_btree *cmd_node)
{
	t_btree		*node;
	t_command	*cmd;

	if (!cmd_node || cmd_node->type != BTREE_COMMAND_TYPE || !redir_node)
		return ;
	node = cmd_node;
	cmd = (t_command *)node->content;
	if (redir_node->type == REDIRECTION_OUT_TYPE)
	{
		safe_close(cmd->out_pipe.write);
		cmd->out_pipe.write = redir_node->fd;
	}
	else if (redir_node->type == REDIRECTION_IN_TYPE
		|| redir_node->type == REDIRECTION_HERE_DOC_TYPE)
	{
		safe_close(cmd->in_pipe.read);
		cmd->in_pipe.read = redir_node->fd;
	}
}

void	link_commands_redirections(t_btree *tree)
{
	t_btree				*node;
	t_btree_redir_node	*redir;

	node = tree;
	while (node)
	{
		if (node->type == BTREE_REDIRECTION_TYPE)
		{
			redir = (t_btree_redir_node *)node->content;
			if (redir && (redir->type == REDIRECTION_IN_TYPE
					|| redir->type == REDIRECTION_HERE_DOC_TYPE) && node->left)
			{
				if (node->left->type == BTREE_COMMAND_TYPE)
					link_redirection_to_cmd_node(redir, node->left);
				else if (recusrive_left_get(node, BTREE_COMMAND_TYPE))
					((t_command *)recusrive_left_get(node,
								BTREE_COMMAND_TYPE)->content)->in_pipe = \
								get_pipe();
			}
			else if (redir && redir->type == REDIRECTION_OUT_TYPE && node->prev)
				link_redirection_to_cmd_node(redir, recusrive_prev_get(node,
						BTREE_COMMAND_TYPE));
		}
		node = node->left;
	}
}
