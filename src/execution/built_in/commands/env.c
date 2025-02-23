/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:33:52 by rguigneb          #+#    #+#             */
/*   Updated: 2025/02/19 12:34:20 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "paths.h"

#define ENV_TOO_MANY_ARGS "env: too many arguments\n"
#define ENV_EXIT_FAILURE 125

int	env_command(t_minishell *data, t_command *command)
{
	int	i;

	i = -1;
	if (char_array_len(command->argv) > 1)
	{
		ft_fprintf(STDERR_FILENO, ENV_TOO_MANY_ARGS);
		return (ENV_EXIT_FAILURE);
	}
	while (data->envp && data->envp[++i])
		if (ft_strchr(data->envp[i], '=') != NULL)
			ft_fprintf(command->out_pipe.write, "%s\n", data->envp[i]);
	return (EXIT_SUCCESS);
}
