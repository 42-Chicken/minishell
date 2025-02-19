/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:33:52 by rguigneb          #+#    #+#             */
/*   Updated: 2025/02/19 10:00:21 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			ft_fprintf(STDOUT_FILENO, command->argv[i]);
			if (i + 1 < len)
				ft_fprintf(STDOUT_FILENO, " ");
		}
	}
	if (new_line)
		ft_fprintf(STDOUT_FILENO, "\n");
	return (EXIT_SUCCESS);
}
