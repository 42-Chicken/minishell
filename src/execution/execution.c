/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 12:23:29 by rguigneb          #+#    #+#             */
/*   Updated: 2025/02/17 15:52:57 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"

bool	handle_commands(t_minishell *data, t_btree_command_node *cmd_node,
		t_btree_node_type condition)
{
	execute_commands_list(data, cmd_node->commands[0]);
	wait_all_commands_executions(data);
	if (condition == BTREE_AND_TYPE && data->exit_code == 0)
	{
		execute_commands_list(data, cmd_node->commands[1]);
		wait_all_commands_executions(data);
		if (data->exit_code != 0)
			return (false);
	}
	else if (condition == BTREE_OR_TYPE && data->exit_code != 0)
	{
		execute_commands_list(data, cmd_node->commands[1]);
		wait_all_commands_executions(data);
		if (data->exit_code != 0)
			return (false);
	}
	return (true);
}

void	recusrive_execute_binary_tree(t_minishell *data, t_btree *node,
		t_btree_node_type type)
{
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
		if (handle_commands(data, (t_btree_command_node *)node->content, type))
			recusrive_execute_binary_tree(data, node->prev->right, BTREE_NONE_TYPE);
	}
}

void	execute_binary_tree(t_minishell *data)
{
	(void)data;
	// recusrive_execute_binary_tree(data, data->execution_tree, BTREE_NONE_TYPE);
}
