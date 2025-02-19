/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:33:52 by rguigneb          #+#    #+#             */
/*   Updated: 2025/02/19 08:43:13 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "paths.h"

#define PWD_TOO_MANY_ARGS "pwd: too many arguments\n"
#define PWD_COULD_NOT_OPEN_WORKING_DIRECTORY "minishell: could not open\
 working directory"

int	pwd_command(t_minishell *data, t_command *command)
{
	char	*path;

	if (char_array_len(command->argv) > 1)
	{
		ft_fprintf(STDOUT_FILENO, PWD_TOO_MANY_ARGS);
		return (EXIT_FAILURE);
	}
	path = get_current_path(data);
	if (path)
		ft_fprintf(STDOUT_FILENO, "%s\n", path);
	else
		ft_fprintf(STDERR_FILENO, PWD_COULD_NOT_OPEN_WORKING_DIRECTORY);
	return (EXIT_SUCCESS);
}
