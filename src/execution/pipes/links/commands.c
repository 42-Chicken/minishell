/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 12:29:52 by rguigneb          #+#    #+#             */
/*   Updated: 2025/02/20 08:39:35 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "binary_tree.h"
#include "execution.h"
#include "minishell.h"

static t_pipe	init_prev_command_pipe(t_btree *cmd_node)
{
	t_command	*cmd;

	if (!cmd_node)
		return (DEFAULT_PIPE);
	if (!cmd_node || !cmd_node->content || cmd_node->type != BTREE_COMMAND_TYPE)
		return (DEFAULT_PIPE);
	cmd = (t_command *)cmd_node->content;
	cmd->out_pipe = get_pipe();
	return (cmd->out_pipe);
}

static void	link_redirection_to_cmd_node(t_btree_redirection_node *redir_node,
		t_btree *cmd_node)
{
	t_btree		*node;
	t_command	*cmd;

	if (!cmd_node || !redir_node)
		return ;
	node = cmd_node->prev;
	if (!node || !node->content || node->type != BTREE_COMMAND_TYPE)
		return ;
	cmd = (t_command *)node->content;
	if (redir_node->type == REDIRECTION_OUT_TYPE)
		cmd->out_pipe = get_pipe();
	else if (redir_node->type == REDIRECTION_IN_TYPE)
		cmd->in_pipe = get_pipe();
}

void	link_commands_redirections(t_btree *redir_node)
{
	t_pipe						pipe;
	t_btree						*node;
	t_btree_redirection_node	*redir;

	pipe = DEFAULT_PIPE;
	node = redir_node;
	if (!redir_node || !redir_node->content
		|| redir_node->type != BTREE_COMMAND_TYPE)
		return ;
	while (node)
	{
		if (node->type == BTREE_REDIRECTION_TYPE && node->content)
		{
			redir = (t_btree_redirection_node *)node->content;
			if (redir && redir->type == REDIRECTION_IN_TYPE && redir_node->prev)
				link_redirection_to_cmd_node(redir, redir_node->prev);
			else if (redir && redir->type == REDIRECTION_OUT_TYPE
				&& redir_node->left)
				link_redirection_to_cmd_node(redir, redir_node->left);
		}
		node = node->left;
	}
}

void	link_commands_pipes(t_btree *cmd_node)
{
	t_pipe		pipe;
	t_btree		*node;
	t_btree		*next;
	t_command	*current;

	pipe = DEFAULT_PIPE;
	node = cmd_node;
	while (node)
	{
		if (node->type == BTREE_PIPE_TYPE && node->prev && node->left)
		{
			pipe = init_prev_command_pipe(get_first_previous(node, BTREE_COMMAND_TYPE));
			next = recusrive_left_get(node, BTREE_COMMAND_TYPE);
			if (next)
			{
				current = (t_command *)next->content;
				current->in_pipe = pipe;
			}
		}
		node = node->left;
	}
}
