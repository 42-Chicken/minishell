/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bind.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 13:26:59 by rguigneb          #+#    #+#             */
/*   Updated: 2025/03/12 08:30:27 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "define.h"
#include "execution.h"
#include "minishell.h"
#include "paths.h"

static char	*get_full_path(const char *path)
{
	return (ft_strjoin(path, "/"));
}

static bool	set_errors(t_command *command, char *name, bool first)
{
	if (access(name, F_OK) == -1)
	{
		if (is_path(name) && first)
			command->error = COMMAND_NO_SUCH_FILE_OR_DIRECTORY_ERROR;
		else
			command->error = COMMAND_NOT_FOUND_ERROR;
		return (true);
	}
	else if (access(name, X_OK) == -1)
	{
		command->error = COMMAND_PERMISSION_DENIED_ERROR;
		return (true);
	}
	command->error = COMMAND_NO_ERROR;
	command->argv[0] = name;
	return (false);
}

static void	try_access(t_command *command, char *path)
{
	int		i;
	char	**path_env;
	char	*name;

	i = 0;
	path_env = ft_split(path, ":");
	while (path_env && path_env[i])
	{
		name = ft_strjoin(get_full_path(path_env[i++]), command->argv[0]);
		if (!set_errors(command, name, false))
			break ;
	}
	set_errors(command, command->argv[0], true);
}

static void	bind_command(t_btree **head, t_btree *node, t_minishell *data)
{
	t_command	*command;
	char		*path;

	(void)head;
	command = (t_command *)node->content;
	if (is_built_in_command(command) || !command->argv || !command->argv[0])
		return ;
	path = (char *)get_env((char const **)data->envp, ENV_PATH);
	if (!path)
		return ;
	if (command->argv[0][0] == '.' && command->argv[0][1] == '.'
		&& command->argv[0][2] == 0)
		command->error = COMMAND_NOT_FOUND_ERROR;
	else if (command->argv[0][0] == '.' && command->argv[0][1] == 0)
		command->error = COMMAND_ARGUMENT_REQUIRED_ERROR;
	else if (is_path(command->argv[0]) && is_directory_file(command->argv[0])
		&& access(command->argv[0], F_OK) != -1)
		command->error = COMMAND_IS_SUCH_FILE_OR_DIRECTORY_ERROR;
	else
		try_access(command, path);
}

void	bind_commands_to_executable(t_minishell *data)
{
	btree_type_foreach_other(&data->execution_tree, BTREE_COMMAND_TYPE,
		(void (*)(t_btree **, t_btree *, void *))bind_command, data);
}
