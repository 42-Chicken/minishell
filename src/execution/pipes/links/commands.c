/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 12:29:52 by rguigneb          #+#    #+#             */
/*   Updated: 2025/02/19 13:01:51 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "binary_tree.h"
#include "execution.h"

void	link_commands_pipes(t_list *lst, t_pipe default_in_pipe,
		t_pipe default_out_pipe)
{
	t_list		*node;
	t_list		*prev;
	t_command	*current;
	t_pipe		prev_out_pipe;

	node = lst;
	prev = NULL;
	prev_out_pipe = default_in_pipe;
	while (node)
	{
		current = (t_command *)node->content;
		current->in_pipe = prev_out_pipe;
		if (node->next)
		{
			current->part_of_pipe = true;
			prev_out_pipe = get_pipe();
			current->out_pipe = prev_out_pipe;
		}
		else
		{
			if (prev)
				current->part_of_pipe = true;
			current->out_pipe = default_out_pipe;
		}
		prev = node;
		node = node->next;
	}
}
