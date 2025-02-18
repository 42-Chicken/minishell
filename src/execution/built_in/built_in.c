/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:31:09 by rguigneb          #+#    #+#             */
/*   Updated: 2025/02/18 15:03:16 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"

void	execute_built_in_command(t_minishell *data, t_command *command)
{
	int	exit_code;

	if (!data || !command || !command->argv || !command->argv[0])
		return ;
	if (ft_strncmp(command->argv[0], "cd", ft_strlen(command->argv[0])) == 0)
		exit_code = cd_command(data, command);
	else if (ft_strncmp(command->argv[0], "echo", ft_strlen(command->argv[0])) == 0)
		exit_code = echo_command(data, command);
	else if (ft_strncmp(command->argv[0], "pwd", ft_strlen(command->argv[0])) == 0)
		exit_code = pwd_command(data, command);
	else if (ft_strncmp(command->argv[0], "unset", ft_strlen(command->argv[0])) == 0)
		exit_code = unset_command(data, command);
	else if (ft_strncmp(command->argv[0], "export",
			ft_strlen(command->argv[0])) == 0)
		exit_code = export_command(data, command);
	else if (ft_strncmp(command->argv[0], "env", ft_strlen(command->argv[0])) == 0)
		exit_code = env_command(data, command);
	else if (ft_strncmp(command->argv[0], "exit", ft_strlen(command->argv[0])) == 0)
		exit_code = exit_command(data, command);
	else
		return ;
	data->exit_code = exit_code;
	safe_exit(EXIT_SUCCESS);
}
