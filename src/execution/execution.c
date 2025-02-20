/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 12:23:29 by rguigneb          #+#    #+#             */
/*   Updated: 2025/02/20 14:55:57 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"

static void	execute_commands_and_wait(t_minishell *data, t_btree *node)
{
	t_btree		*current;
	t_command	*command;

	current = node;
	while (current)
	{
		if (current->type == BTREE_COMMAND_TYPE && current->content)
		{
			command = (t_command *)current->content;
			exec_command(data, current, command);
		}
		current = current->left;
	}
	wait_all_commands_executions(data);
}

static void	handle_commands(t_minishell *data, t_btree *node)
{
	link_commands_pipes(node);
	link_commands_redirections(node);
	execute_commands_and_wait(data, node);
}

void	recusrive_execute_binary_tree(t_minishell *data, t_btree *node)
{
	if (!node)
		return ;
	if (node->type == BTREE_AND_TYPE)
	{
		if (node->left && node->left->type == BTREE_COMMAND_TYPE)
		{
			handle_commands(data, node->left);
			if (data->exit_code == 0)
				handle_commands(data, node->right);
		}
		else
			recusrive_execute_binary_tree(data, node->left);
	}
	else if (node->type == BTREE_PIPE_TYPE
		|| node->type == BTREE_REDIRECTION_TYPE)
	{
		handle_commands(data, node);
	}
	else if (node->type == BTREE_OR_TYPE)
	{
		if (node->left && node->left->type == BTREE_COMMAND_TYPE)
		{
			handle_commands(data, node->left);
			if (data->exit_code != 0)
				handle_commands(data, node->right);
		}
		else
			recusrive_execute_binary_tree(data, node->left);
	}
	else if (node->type == BTREE_COMMAND_TYPE)
	{
		handle_commands(data, node);
	}
}

void	execute_binary_tree(t_minishell *data)
{
	recusrive_execute_binary_tree(data, data->execution_tree);
}
