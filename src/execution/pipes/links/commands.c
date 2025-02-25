/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 12:29:52 by rguigneb          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/02/19 15:30:10 by rguigneb         ###   ########.fr       */
=======
/*   Updated: 2025/02/20 15:27:29 by rguigneb         ###   ########.fr       */
>>>>>>> romain
/*                                                                            */
/* ************************************************************************** */

#include "binary_tree.h"
#include "execution.h"
#include "minishell.h"

static t_pipe	init_prev_command_pipe(t_btree *cmd_node)
{
	t_command	*cmd;

	if (!cmd_node)
		return ((t_pipe){PIPE_NO_VALUE, PIPE_NO_VALUE});
	if (!cmd_node || !cmd_node->content || cmd_node->type != BTREE_COMMAND_TYPE)
		return ((t_pipe){PIPE_NO_VALUE, PIPE_NO_VALUE});
	cmd = (t_command *)cmd_node->content;
	cmd->part_of_pipe = true;
	cmd->out_pipe = get_pipe();
	return (cmd->out_pipe);
}

<<<<<<< HEAD
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

=======
>>>>>>> romain
void	link_commands_pipes(t_btree *cmd_node)
{
	t_pipe		pipe;
	t_btree		*node;
	t_btree		*next;
	t_command	*current;

	pipe = (t_pipe){PIPE_NO_VALUE, PIPE_NO_VALUE};
	node = cmd_node;
	while (node)
	{
		if (node->type == BTREE_PIPE_TYPE && node->prev && node->left)
		{
			pipe = init_prev_command_pipe(get_first_previous(node,
						BTREE_COMMAND_TYPE));
			next = recusrive_left_get(node, BTREE_COMMAND_TYPE);
			if (next)
			{
				current = (t_command *)next->content;
				current->in_pipe = pipe;
				current->part_of_pipe = true;
			}
		}
		node = node->left;
	}
}
