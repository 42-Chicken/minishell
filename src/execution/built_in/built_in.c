/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:31:09 by rguigneb          #+#    #+#             */
/*   Updated: 2025/03/13 16:50:48 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "define.h"
#include "execution.h"
#include "minishell.h"

static void	handle_execution(t_minishell *data, t_command *command,
		int (*func)(t_minishell *, t_command *))
{
	create_safe_memory_context();
	if ((command->out_redir
			&& command->out_redir->error != REDIRECTION_NO_ERROR)
		|| (command->in_redir
			&& command->in_redir->error != REDIRECTION_NO_ERROR))
		data->exit_code = 1;
	else
		data->exit_code = func(data, command);
	exit_safe_memory_context();
}

bool	is_built_in_command(t_command *command)
{
	if (!command || !command->argv)
		return (false);
	if (is_same_str(command->argv[0], CD_BT))
		return (true);
	else if (is_same_str(command->argv[0], ECHO_BT))
		return (true);
	else if (is_same_str(command->argv[0], PWD_BT))
		return (true);
	else if (is_same_str(command->argv[0], UNSET_BT))
		return (true);
	else if (is_same_str(command->argv[0], EXPORT_BT))
		return (true);
	else if (is_same_str(command->argv[0], ENV_BT))
		return (true);
	else if (is_same_str(command->argv[0], EXIT_BT))
		return (true);
	else
		return (false);
}

bool	execute_built_in_command(t_minishell *data, t_command *command)
{
	if (!data || !command || !command->argv || !command->argv[0])
		return (true);
	if (is_same_str(command->argv[0], CD_BT))
		handle_execution(data, command, cd_command);
	else if (is_same_str(command->argv[0], ECHO_BT))
		handle_execution(data, command, echo_command);
	else if (is_same_str(command->argv[0], PWD_BT))
		handle_execution(data, command, pwd_command);
	else if (is_same_str(command->argv[0], UNSET_BT))
		handle_execution(data, command, unset_command);
	else if (is_same_str(command->argv[0], EXPORT_BT))
		handle_execution(data, command, export_command);
	else if (is_same_str(command->argv[0], ENV_BT))
		handle_execution(data, command, env_command);
	else if (is_same_str(command->argv[0], EXIT_BT))
		handle_execution(data, command, exit_command);
	else
		return (false);
	return (true);
}
