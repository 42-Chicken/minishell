/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 12:23:29 by rguigneb          #+#    #+#             */
/*   Updated: 2025/02/18 10:57:30 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"

static void	execute_commands_and_wait(t_minishell *data, t_btree *node)
{
	t_list	*cmds_list;

	cmds_list = (t_list *)node->content;
	link_commands_pipes(cmds_list, (t_pipe){PIPE_NO_VALUE, PIPE_NO_VALUE},
		(t_pipe){PIPE_NO_VALUE, STDOUT_FILENO});
	execute_commands_list(data, cmds_list);
	wait_all_commands_executions(data);
}

static bool	handle_commands(t_minishell *data, t_btree *node,
		t_btree_node_type condition)
{
	execute_commands_and_wait(data, node->right);
	if (condition == BTREE_AND_TYPE && data->exit_code == 0)
	{
		execute_commands_and_wait(data, node->left);
		if (data->exit_code != 0)
			return (false);
	}
	else if (condition == BTREE_OR_TYPE && data->exit_code != 0)
	{
		execute_commands_and_wait(data, node->left);
		if (data->exit_code != 0)
			return (false);
	}
	return (true);
}

void	recusrive_execute_binary_tree(t_minishell *data, t_btree *node,
		t_btree_node_type type)
{
	if (!node)
		return ;
	if (node->type == BTREE_AND_TYPE)
	{
		recusrive_execute_binary_tree(data, node->left, BTREE_AND_TYPE);
	}
	else if (node->type == BTREE_OR_TYPE)
	{
		recusrive_execute_binary_tree(data, node->left, BTREE_OR_TYPE);
	}
	else if (node->type == BTREE_COMMANDS_TYPE)
	{
		if (handle_commands(data, node, type))
			recusrive_execute_binary_tree(data, node->prev->right,
				BTREE_NONE_TYPE);
	}
}

void	execute_binary_tree(t_minishell *data)
{
	recusrive_execute_binary_tree(data, data->execution_tree, BTREE_NONE_TYPE);
}
