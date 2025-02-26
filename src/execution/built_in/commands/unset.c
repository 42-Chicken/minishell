/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:33:52 by rguigneb          #+#    #+#             */
/*   Updated: 2025/02/26 09:53:55 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unset_command(t_minishell *data, t_command *command)
{
	int	i;
	int	index;

	i = 0;
	if (char_array_len(command->argv) >= 1)
	{
		while (command->argv[++i])
		{
			index = custom_get_var_env_index(data->envp, command->argv[i]);
			if (index != -1 && !ft_strchr(command->argv[i], '='))
				remove_from_env_index(&data->envp, index);
		}
	}
	return (EXIT_SUCCESS);
}
