/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:33:52 by rguigneb          #+#    #+#             */
/*   Updated: 2025/02/19 09:56:18 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "paths.h"

#define CD_HOME_NOT_SET "minishell: cd: HOME not set\n"
#define CD_COULD_NOT_OPEN_WORKING_DIRECTORY "minishell: could not open\
 working directory\n"
#define CD_COULD_NOT_FIND_DIRECTORY "bash: cd: %s: No such file or directory\n"

static void	update_env(t_minishell *data, char *key)
{
	char	*path;

	path = get_current_path(data);
	if (!path)
	{
		ft_fprintf(STDERR_FILENO, CD_COULD_NOT_OPEN_WORKING_DIRECTORY);
		safe_exit(EXIT_FAILURE);
	}
	set_env(&data->envp, key, path);
}

static char	*get_home(t_minishell *data)
{
	char	*home_path;

	home_path = get_home_path(data);
	if (!home_path)
	{
		ft_fprintf(STDERR_FILENO, CD_HOME_NOT_SET);
		safe_exit(EXIT_FAILURE);
	}
	return (home_path);
}

int	cd_command(t_minishell *data, t_command *command)
{
	char	*target_path;

	if (!command->argv || !command->argv[0])
		return (EXIT_FAILURE);
	if (char_array_len(command->argv) == 1)
		target_path = get_home(data);
	else
	{
		if (command->argv[1][0] == '~')
			target_path = ft_strjoin(get_home(data), command->argv[1] + 1);
		else
			target_path = command->argv[1];
	}
	update_env(data, "OLDPWD");
	if (chdir(target_path) == -1)
		return (ft_fprintf(STDERR_FILENO, CD_COULD_NOT_FIND_DIRECTORY,
				target_path), EXIT_FAILURE);
	update_env(data, "PWD");
	return (EXIT_SUCCESS);
}
