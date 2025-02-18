/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:31:09 by rguigneb          #+#    #+#             */
/*   Updated: 2025/02/18 15:38:42 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"

static bool	is_same_str(char *str1, char *str2)
{
	return (ft_strncmp(str1, str2, ft_strlen(str1)) == 0);
}

void	execute_built_in_command(t_minishell *data, t_command *command)
{
	int	exit_code;

	if (!data || !command || !command->argv || !command->argv[0])
		return ;
	if (is_same_str(command->argv[0], "cd"))
		exit_code = cd_command(data, command);
	else if (is_same_str(command->argv[0], "echo"))
		exit_code = echo_command(data, command);
	else if (is_same_str(command->argv[0], "pwd"))
		exit_code = pwd_command(data, command);
	else if (is_same_str(command->argv[0], "unset"))
		exit_code = unset_command(data, command);
	else if (is_same_str(command->argv[0], "export"))
		exit_code = export_command(data, command);
	else if (is_same_str(command->argv[0], "env"))
		exit_code = env_command(data, command);
	else if (is_same_str(command->argv[0], "exit"))
		exit_code = exit_command(data, command);
	else
		return ;
	data->exit_code = exit_code;
	safe_exit(EXIT_SUCCESS);
}
