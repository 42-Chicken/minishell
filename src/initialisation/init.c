/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 10:55:13 by rguigneb          #+#    #+#             */
/*   Updated: 2025/02/14 11:56:39 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "signals.h"

void	init_minishell(t_minishell *data)
{
	init_signals(data);
	if (getcwd((char *)&data->started_path, MAX_PATH_LENGTH) == NULL)
	{
		data->stop = true;
		ft_fprintf(STDERR_FILENO, "Cannot access current working directory !\n");
	}
	set_env(&data->envp, "PWD", (char *)data->started_path);
}
