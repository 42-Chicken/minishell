/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:33:52 by rguigneb          #+#    #+#             */
/*   Updated: 2025/02/18 15:35:46 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "paths.h"

#define PWD_TOO_MANY_ARGS "pwd: too many arguments\n"

int	pwd_command(t_minishell *data, t_command *command)
{
	if (char_array_len(command->argv) > 1)
	{
		ft_fprintf(STDOUT_FILENO, PWD_TOO_MANY_ARGS);
		return (EXIT_FAILURE);
	}
	ft_fprintf(STDOUT_FILENO, "%s\n", get_current_path(data));
	return (EXIT_SUCCESS);
}
