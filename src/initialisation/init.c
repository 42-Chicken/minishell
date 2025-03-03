/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 10:55:13 by rguigneb          #+#    #+#             */
/*   Updated: 2025/03/03 08:30:29 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "define.h"
#include "minishell.h"
#include "paths.h"
#include "signals.h"

void	init_minishell(t_minishell *data)
{
	reset_signals(true);
	if (getcwd((char *)&data->started_path, MAX_PATH_LENGTH) == NULL)
	{
		data->stop = true;
		ft_fprintf(STDERR_FILENO, ERROR_CANNOT_ACCESS_WORKING_DIRECTORY);
	}
	set_current_path(data, (char *)data->started_path);
	set_env(&data->envp, (char *)"_", "/usr/bin/env");
	set_env(&data->envp, (char *)"TERM", "xterm-256color");
	data->line_count = 1;
	update_shlvl(data, (char *)get_env(data->envp, ENV_SHLVL), 0);
}
