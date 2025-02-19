/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:31:09 by rguigneb          #+#    #+#             */
/*   Updated: 2025/02/19 11:15:08 by rguigneb         ###   ########.fr       */
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
	// int	in;
	// int	out;

	create_safe_memory_context();
	// if (command->in_pipe.write)
	// 	safe_close(command->in_pipe.write);
	// if (command->in_pipe.read)
	// 	safe_close(command->out_pipe.read);
	// in = dup(STDIN_FILENO);
	// out = dup(STDOUT_FILENO);
	// dup2(command->in_pipe.read, STDIN_FILENO);
	// dup2(command->out_pipe.write, STDOUT_FILENO);
	data->exit_code = func(data, command);
	// dup2(command->in_pipe.read, STDIN_FILENO);
	// dup2(command->out_pipe.write, STDOUT_FILENO);
	// safe_close(in);
	// safe_close(out);
	// safe_close(command->in_pipe.read);
	// safe_close(command->out_pipe.write);
	exit_safe_memory_context();
}

static bool	is_not_in_pipe(t_list *cmds_list)
{
	return (ft_lstsize(cmds_list) == 1); // to test
}

bool	execute_built_in_command(t_minishell *data, t_list *cmds_list,
		t_command *command)
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
	else if (is_same_str(command->argv[0], "exit") && is_not_in_pipe(cmds_list))
		handle_execution(data, command, exit_command);
	else
		return (false);
	return (true);
}
