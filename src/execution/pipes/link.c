/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 08:30:35 by rguigneb          #+#    #+#             */
/*   Updated: 2025/02/17 12:07:42 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"

void	commands_list_pipes_linking(t_minishell *data,
		t_btree_command_node *cmd_node)
{
	t_list		*node;
	t_command	*current;
	t_pipe		prev_out_pipe;

	if (!data || !cmd_node)
		return ;
	node = cmd_node->commands;
	prev_out_pipe = cmd_node->in_pipe;
	while (node)
	{
		current = (t_command *)node->content;
		current->in_pipe = prev_out_pipe;
		if (node->next)
		{
			prev_out_pipe = get_pipe();
			current->out_pipe = prev_out_pipe;
		}
		else
			current->out_pipe = cmd_node->out_pipe;
		node = node->next;
	}
}

void	redirection_pipes_linking(t_minishell *data, t_btree *node)
{
	t_btree						*target;
	t_btree_redirection_node	*redirection_content;
	t_btree_command_node		*cmd_node;

	(void)data;
	redirection_content = (t_btree_redirection_node *)node->content;
	if (redirection_content->type == REDIRECTION_IN_TYPE)
	{
		target = get_first_previous(node, BTREE_COMMANDS_TYPE);
		if (!target)
			return ;
		cmd_node = (t_btree_command_node *)target->content;
		cmd_node->in_pipe = (t_pipe){redirection_content->fd, PIPE_NO_VALUE};
	}
	else
	{
		target = recusrive_left_get(node, BTREE_COMMANDS_TYPE);
		if (!target)
			return ;
		cmd_node = (t_btree_command_node *)target->content;
		cmd_node->out_pipe = (t_pipe){PIPE_NO_VALUE, redirection_content->fd};
	}
}

static void	execute_redirection_foreach(t_btree **head, t_btree *node,
		void *other)
{
	if (!head || !node)
		return ;
	if (node->type == BTREE_REDIRECTION_TYPE)
		redirection_pipes_linking((t_minishell *)other, node);
}

static void	execute_commands_foreach(t_btree **head, t_btree *node, void *other)
{
	if (!head || !node)
		return ;
	if (node->type == BTREE_COMMANDS_TYPE)
		commands_list_pipes_linking((t_minishell *)other, (t_btree_command_node *)node->content);
}

void	link_execution_tree_pipes(t_minishell *data)
{
	if (!data || !data->execution_tree)
		return ;
	btree_foreach(&data->execution_tree, execute_redirection_foreach,
		(void *)data);
	btree_foreach(&data->execution_tree, execute_commands_foreach, (void *)data);
}
