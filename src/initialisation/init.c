/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 10:55:13 by rguigneb          #+#    #+#             */
/*   Updated: 2025/02/25 09:15:02 by rguigneb         ###   ########.fr       */
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
	data->line_count = 1;
	update_shlvl(data, (char *)get_env(data->envp, ENV_SHLVL), 0);
}
