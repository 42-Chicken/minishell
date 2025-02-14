/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 10:55:13 by rguigneb          #+#    #+#             */
/*   Updated: 2025/02/14 13:04:50 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "signals.h"
#include "paths.h"

void	init_minishell(t_minishell *data)
{
	init_signals(data);
	if (getcwd((char *)&data->started_path, MAX_PATH_LENGTH) == NULL)
	{
		data->stop = true;
		ft_fprintf(STDERR_FILENO, "Cannot access current working directory !\n");
	}
	set_current_path(data, (char *)data->started_path);
}
