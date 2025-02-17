/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:24:39 by rguigneb          #+#    #+#             */
/*   Updated: 2025/02/17 15:43:31 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"

void	execute_commands_list(t_minishell *data, t_list *lst)
{
	t_list		*current;

	current = lst;
	(void)current;
	(void)data;
	// while (current)
	// {
	// 	command = (t_command *)current->content;
	// 	exec_command(command);
	// 	current = current->next;
	// }
}
