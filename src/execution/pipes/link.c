/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 08:30:35 by rguigneb          #+#    #+#             */
/*   Updated: 2025/02/17 09:29:59 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"

void	recursive_tree_pipes_linking(t_minishell *data, t_command *command,
		t_pipe default_pipe)
{
	if (!data || !command)
		return ;
	if (command->next && command->next[SUCCESS] && command->next[FAILED]
		&& command->next[SUCCESS] == command->next[FAILED])
	{
		command->out_pipe = get_pipe();
		set_pipe(&command->next[SUCCESS]->in_pipe, command->out_pipe);
	}
	else
		set_pipe(&command->out_pipe, default_pipe);
	if (command->subtree)
		recursive_tree_pipes_linking(data, command, command->in_pipe);
}

void	link_execution_tree_pipes(t_minishell *data)
{
	if (!data || !data->execution_tree)
		return ;
	recursive_tree_pipes_linking(data, data->execution_tree,
		(t_pipe){PIPE_NO_VALUE, STDOUT_FILENO});
}
