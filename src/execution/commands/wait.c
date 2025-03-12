/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:28:29 by rguigneb          #+#    #+#             */
/*   Updated: 2025/03/12 09:31:08 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"

void	wait_all_commands_executions(t_minishell *data)
{
	pid_t	wpid;
	int		status;

	wpid = 1;
	status = 0;
	while (wpid > 0)
	{
		wpid = wait(&status);
		if (wpid > 0 && WIFEXITED(status))
			data->exit_code = WEXITSTATUS(status);
	}
}
