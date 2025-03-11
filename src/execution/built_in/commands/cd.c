/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:33:52 by rguigneb          #+#    #+#             */
/*   Updated: 2025/03/11 11:47:52 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "paths.h"
#include "define.h"

#define CD_HOME_NOT_SET "minishell: cd: HOME not set\n"
#define CD_COULD_NOT_OPEN_WORKING_DIRECTORY "minishell: could not open\
 working directory\n"
#define CD_COULD_NOT_FIND_DIRECTORY "minishell\
: cd: %s: No such file or directory\n"

static bool	update_env(t_minishell *data, t_command *command, char *key)
{
	char	*path;

	if (command->part_of_pipe || command->priority != 0)
		return (true);
	path = get_current_path(data);
	if (!path)
	{
		ft_fprintf(STDERR_FILENO, CD_COULD_NOT_OPEN_WORKING_DIRECTORY);
		return (false);
	}
	set_env(&data->envp, key, path);
	return (true);
}

static char	*get_home(t_minishell *data)
{
	char	*home_path;

	home_path = get_home_path(data);
	if (!home_path)
	{
		ft_fprintf(STDERR_FILENO, CD_HOME_NOT_SET);
		return (NULL);
	}
	return (home_path);
}

int	cd_command(t_minishell *data, t_command *command)
{
	char	*target_path;

	target_path = NULL;
	if (char_array_len(command->argv) == 1)
		target_path = get_home(data);
	else
	{
		if (command->argv[1][0] == HOME_DIRECTORY_REPRESENTATION[0]
			&& get_home(data))
			target_path = ft_strjoin(get_home(data), command->argv[1] + 1);
		else
			target_path = command->argv[1];
	}
	if (!target_path)
		return (EXIT_FAILURE);
	if (!update_env(data, command, ENV_OLDPWD))
		return (EXIT_FAILURE);
	if ((command->part_of_pipe && access(target_path, F_OK) == -1)
		|| (command->priority == 0 && !command->part_of_pipe
			&& chdir(target_path) == -1))
		return (ft_fprintf(STDERR_FILENO, CD_COULD_NOT_FIND_DIRECTORY,
				target_path), EXIT_FAILURE);
	if (!update_env(data, command, ENV_PWD))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
