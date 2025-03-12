/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:33:52 by rguigneb          #+#    #+#             */
/*   Updated: 2025/03/12 09:06:04 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "define.h"
#include "minishell.h"
#include "paths.h"

#define PWD_TOO_MANY_ARGS "pwd: too many arguments\n"

int	pwd_command(t_minishell *data, t_command *command)
{
	char	*path;

	// if (char_array_len(command->argv) > 1)
	// {
	// 	ft_fprintf(command->out_pipe.write, PWD_TOO_MANY_ARGS);
	// 	return (EXIT_FAILURE);
	// }
	path = get_current_path(data);
	if (path)
		ft_fprintf(command->out_pipe.write, "%s\n", path);
	else
		ft_fprintf(STDERR_FILENO, ERROR_CANNOT_ACCESS_WORKING_DIRECTORY);
	return (EXIT_SUCCESS);
}
