/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:33:52 by rguigneb          #+#    #+#             */
/*   Updated: 2025/03/13 09:06:45 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 	if (write(command->out_pipe.write, 0, 0) == -1)
// return (EXIT_FAILURE);
int	echo_command(t_minishell *data, t_command *command)
{
	int		i;
	bool	new_line;
	int		len;

	(void)data;
	len = char_array_len(command->argv);
	i = 0;
	new_line = true;
	if (len > 1)
	{
		if (!ft_strncmp("-n", command->argv[1], ft_strlen(command->argv[1])))
		{
			new_line = false;
			i = 1;
		}
		while (i < len && command->argv[++i])
		{
			ft_fprintf(command->out_pipe.write, command->argv[i]);
			if (i + 1 < len)
				ft_fprintf(command->out_pipe.write, " ");
		}
	}
	if (new_line && write(command->out_pipe.write, 0, 0) != -1)
		ft_fprintf(command->out_pipe.write, "\n");
	return (EXIT_SUCCESS);
}
