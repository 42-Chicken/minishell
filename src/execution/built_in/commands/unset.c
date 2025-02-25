/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:33:52 by rguigneb          #+#    #+#             */
/*   Updated: 2025/02/20 12:04:15 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unset_command(t_minishell *data, t_command *command)
{
	int	i;
	int	index;

	i = -1;
	if (char_array_len(command->argv) >= 1)
	{
		while (command->argv[++i])
		{
			index = get_raw_env_index(data->envp, command->argv[i]);
			if (index != -1 && !ft_strchr(command->argv[i], '='))
				remove_from_env(&data->envp, command->argv[i]);
			else
			{
				index = get_env_index(data->envp, command->argv[i]);
				if (index != -1)
					remove_from_env(&data->envp, command->argv[i]);
			}
		}
	}
	return (EXIT_SUCCESS);
}
