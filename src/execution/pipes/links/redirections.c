/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 15:27:08 by rguigneb          #+#    #+#             */
/*   Updated: 2025/03/13 16:50:25 by rguigneb         ###   ########.fr       */
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
		cmd->out_redir = redir_node;
	}
	else if (redir_node->type == REDIRECTION_IN_TYPE
		|| redir_node->type == REDIRECTION_HERE_DOC_TYPE)
	{
		safe_close(cmd->in_pipe.read);
		cmd->in_pipe.read = redir_node->fd;
		cmd->in_redir = redir_node;
	}
	if (redir_node->error)
		cmd->should_not_execute = true;
	redir_node->command = cmd;
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
							BTREE_COMMAND_TYPE)->content)->in_pipe = get_pipe();
			}
			else if (redir && redir->type == REDIRECTION_OUT_TYPE && node->prev)
				link_redirection_to_cmd_node(redir, recusrive_prev_get(node,
						BTREE_COMMAND_TYPE));
		}
		node = node->left;
	}
}

void	link_redir_command(t_btree_redir_node *redir, t_command *command)
{
	redir->command = command;
	command->in_redir = redir;
}

void	idk_i_just_want_to_finish_that(t_btree **head, t_btree *node)
{
	t_btree_redir_node	*redir;

	(void)head;
	redir = (t_btree_redir_node *)node->content;
	if (redir && (redir->type == REDIRECTION_IN_TYPE
			|| redir->type == REDIRECTION_HERE_DOC_TYPE) && node->left)
	{
		if (node->left->type == BTREE_COMMAND_TYPE)
			link_redir_command(redir, (t_command *)node->left->content);
		else if (recusrive_left_get(node, BTREE_COMMAND_TYPE))
			link_redir_command(redir, (t_command *)recusrive_left_get(node,
					BTREE_COMMAND_TYPE)->content);
	}
	else if (redir && redir->type == REDIRECTION_OUT_TYPE && node->prev
		&& recusrive_prev_get(node, BTREE_COMMAND_TYPE))
		link_redir_command(redir, (t_command *)recusrive_prev_get(node,
				BTREE_COMMAND_TYPE)->content);
}

void	link_commands_and_redirections_together(t_minishell *data)
{
	btree_type_foreach(&data->execution_tree, BTREE_REDIRECTION_TYPE,
		idk_i_just_want_to_finish_that);
}
