/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 10:55:13 by rguigneb          #+#    #+#             */
/*   Updated: 2025/02/25 08:30:47 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "paths.h"
#include "signals.h"

void	init_minishell(t_minishell *data)
{
	reset_signals(true);
	if (getcwd((char *)&data->started_path, MAX_PATH_LENGTH) == NULL)
	{
		data->stop = true;
		ft_fprintf(STDERR_FILENO,
			"Cannot access current working directory !\n");
	}
	set_current_path(data, (char *)data->started_path);
	set_env(&data->envp, "minishell", "true");
	data->line_count = 1;
	update_shlvl(data, (char *)get_env(data->envp, "SHLVL"), 0);
}
