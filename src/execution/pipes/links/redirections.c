/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 12:28:47 by rguigneb          #+#    #+#             */
/*   Updated: 2025/02/17 12:29:27 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "binary_tree.h"
#include "execution.h"

static void	redirection_pipes_linking(t_minishell *data, t_btree *node)
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

void	execute_redirection_foreach(t_btree **head, t_btree *node, void *other)
{
	if (!head || !node)
		return ;
	if (node->type == BTREE_REDIRECTION_TYPE)
		redirection_pipes_linking((t_minishell *)other, node);
}
