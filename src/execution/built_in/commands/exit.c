/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:33:52 by rguigneb          #+#    #+#             */
/*   Updated: 2025/03/12 09:18:33 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define EXIT_NOT_A_NUMERIC_ARG \
	"minishell\
: exit: %s: numeric argument required\n"
#define EXIT_TOO_MANY_ARG \
	"minishell\
: exit: too many arguments\n"
#define EXIT_NOT_A_NUMERIC_ARG_CODE 2
#define EXIT_TOO_MANY_ARG_CODE 1

int	exit_command(t_minishell *data, t_command *command)
{
	if (!command->part_of_pipe && command->priority == 0)
		ft_fprintf(STDOUT_FILENO, "exit\n");
	if (char_array_len(command->argv) > 2)
		return (ft_fprintf(STDERR_FILENO, EXIT_TOO_MANY_ARG),
			EXIT_TOO_MANY_ARG_CODE);
	if (command->argv[1])
	{
		if (!is_number(command->argv[1]))
		{
			ft_fprintf(STDERR_FILENO, EXIT_NOT_A_NUMERIC_ARG, command->argv[1]);
			safe_exit(EXIT_NOT_A_NUMERIC_ARG_CODE);
		}
		data->exit_code = (unsigned char)ft_atoi(command->argv[1]);
	}
	if (!command->part_of_pipe && command->priority == 0)
		safe_exit(data->exit_code);
	return (data->exit_code);
}
