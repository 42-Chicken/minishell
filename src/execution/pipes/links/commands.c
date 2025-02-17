/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 12:29:52 by rguigneb          #+#    #+#             */
/*   Updated: 2025/02/17 12:36:19 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "binary_tree.h"
#include "execution.h"

static void	link_pipes(t_list *lst, t_btree_command_node *cmd_node)
{
	t_list		*node;
	t_command	*current;
	t_pipe		prev_out_pipe;

	node = lst;
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
static void	commands_list_pipes_linking(t_minishell *data,
		t_btree_command_node *cmd_node)
{
	if (!data || !cmd_node)
		return ;
	link_pipes(cmd_node->commands[0], cmd_node);
	link_pipes(cmd_node->commands[1], cmd_node);
}

void	execute_commands_foreach(t_btree **head, t_btree *node, void *other)
{
	if (!head || !node)
		return ;
	if (node->type == BTREE_COMMANDS_TYPE)
		commands_list_pipes_linking((t_minishell *)other,
			(t_btree_command_node *)node->content);
}
