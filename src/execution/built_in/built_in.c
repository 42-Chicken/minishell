/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:31:09 by rguigneb          #+#    #+#             */
/*   Updated: 2025/02/20 13:18:21 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"

static bool	is_same_str(char *str1, char *str2)
{
	return (ft_strncmp(str1, str2, ft_strlen(str1)) == 0);
}

static void	handle_execution(t_minishell *data, t_command *command,
		int (*func)(t_minishell *, t_command *))
{
	create_safe_memory_context();
	data->exit_code = func(data, command);
	exit_safe_memory_context();
}

bool	is_built_in_command(t_command *command)
{
	if (is_same_str(command->argv[0], "cd"))
		return (true);
	else if (is_same_str(command->argv[0], "echo"))
		return (true);
	else if (is_same_str(command->argv[0], "pwd"))
		return (true);
	else if (is_same_str(command->argv[0], "unset"))
		return (true);
	else if (is_same_str(command->argv[0], "export"))
		return (true);
	else if (is_same_str(command->argv[0], "env"))
		return (true);
	else if (is_same_str(command->argv[0], "exit"))
		return (true);
	else
		return (false);
}

bool	execute_built_in_command(t_minishell *data, t_command *command)
{
	if (!data || !command || !command->argv || !command->argv[0])
		return (true);
	if (is_same_str(command->argv[0], "cd"))
		handle_execution(data, command, cd_command);
	else if (is_same_str(command->argv[0], "echo"))
		handle_execution(data, command, echo_command);
	else if (is_same_str(command->argv[0], "pwd"))
		handle_execution(data, command, pwd_command);
	else if (is_same_str(command->argv[0], "unset"))
		handle_execution(data, command, unset_command);
	else if (is_same_str(command->argv[0], "export"))
		handle_execution(data, command, export_command);
	else if (is_same_str(command->argv[0], "env"))
		handle_execution(data, command, env_command);
	else if (is_same_str(command->argv[0], "exit"))
		handle_execution(data, command, exit_command);
	else
		return (false);
	return (true);
}
