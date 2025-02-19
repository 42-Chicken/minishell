/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 12:29:52 by rguigneb          #+#    #+#             */
/*   Updated: 2025/02/18 09:46:25 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "binary_tree.h"
#include "execution.h"

void	link_commands_pipes(t_list *lst, t_pipe default_in_pipe,
		t_pipe default_out_pipe)
{
	t_list		*node;
	t_command	*current;
	t_pipe		prev_out_pipe;

	node = lst;
	prev_out_pipe = default_in_pipe;
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
			current->out_pipe = default_out_pipe;
		node = node->next;
	}
}
