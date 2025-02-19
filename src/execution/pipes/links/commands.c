/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 12:29:52 by rguigneb          #+#    #+#             */
/*   Updated: 2025/02/19 15:30:10 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "binary_tree.h"
#include "execution.h"

static t_pipe	init_prev_command_pipe(t_btree *cmd_node)
{
	t_btree		*node;
	t_command	*cmd;

	if (!cmd_node)
		return ;
	node = cmd_node->prev;
	if (!node || !node->content || node->type != BTREE_COMMAND_TYPE)
		return (DEFAULT_PIPE);
	cmd = (t_command *)node->content;
	cmd->out_pipe = get_pipe();
	return (cmd->out_pipe);
}

void	link_commands_redirections(t_btree *cmd_node)
{
	t_pipe						pipe;
	t_btree						*node;
	t_command					*current;
	t_btree_redirection_node	*redir_node;

	pipe = DEFAULT_PIPE;
	node = cmd_node;
	if (!cmd_node || !cmd_node->content || cmd_node->type != BTREE_COMMAND_TYPE)
		return ;
	while (node)
	{
		if (node->type == BTREE_REDIRECTION_TYPE)
		{
			redir_node = (t_btree_redirection_node	*)node->content;
			if (redir_node)
				pipe = init_prev_command_pipe(node->prev);
			current = (t_command *)node->left->content;
			current->in_pipe = pipe;
		}
		node = node->left;
	}
}

void	link_commands_pipes(t_btree *cmd_node)
{
	t_pipe		pipe;
	t_btree		*node;
	t_command	*current;

	pipe = DEFAULT_PIPE;
	node = cmd_node;
	if (!cmd_node || !cmd_node->content || cmd_node->type != BTREE_COMMAND_TYPE)
		return ;
	while (node)
	{
		if (node->type == BTREE_PIPE_TYPE && node->prev && node->content
			&& node->left && node->left->content)
		{
			pipe = init_prev_command_pipe(node->prev);
			current = (t_command *)node->left->content;
			current->in_pipe = pipe;
		}
		node = node->left;
	}
}
