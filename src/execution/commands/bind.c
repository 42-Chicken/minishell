/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bind.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 13:26:59 by rguigneb          #+#    #+#             */
/*   Updated: 2025/02/20 14:44:33 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
			command->error = COMMAND_NO_SUCH_FILE_OR_DIRECTORY;
		else
			command->error = COMMAND_NOT_FOUND;
		return (true);
	}
	else if (access(name, X_OK) == -1)
	{
		command->error = COMMAND_PERMISSION_DENIED;
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
	path_env = ft_split(path, ':');
	while (path_env && path_env[i])
	{
		name = ft_strjoin(get_full_path(path_env[i++]), command->argv[0]);
		if (!set_errors(command, name, false))
			break ;
	}
	set_errors(command, command->argv[0], true);
}

static void	bind_command(t_btree *node)
{
	t_command	*command;
	char		*path;

	command = (t_command *)node->content;
	if (is_built_in_command(command))
		return ;
	path = (char *)get_env((char const **)command->envp, "PATH");
	if (!path)
		return ;
	if (is_path(command->argv[0]) && is_directory_file(command->argv[0])
		&& access(command->argv[0], F_OK) != -1)
		command->error = COMMAND_IS_SUCH_FILE_OR_DIRECTORY;
	else
		try_access(command, path);
}

static void	recustive_bind_commands_to_executable(t_btree *node)
{
	if (!node)
		// create a custom function for recustive like this like btreac for each type
		return ;
	if (node->type == BTREE_COMMAND_TYPE)
		bind_command(node);
	recustive_bind_commands_to_executable(node->left);
	recustive_bind_commands_to_executable(node->right);
}

void	bind_commands_to_executable(t_minishell *data)
{
	recustive_bind_commands_to_executable(data->execution_tree);
}
