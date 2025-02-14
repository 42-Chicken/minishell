/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 19:01:37 by romain            #+#    #+#             */
/*   Updated: 2025/02/14 10:44:41 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_readline(t_minishell *data)
{
	char	*line;

	line = readline(get_prompt(data));
	if (line && ft_strncmp(line, "exit", ft_strlen("exit")) == 0)
	{
		free(line);
		safe_exit(1);
	}
	if (line && ft_strlen(line) > 0)
	{
		data->exit_code = 0;
		ft_fprintf(1, RED);
		ft_fprintf(1, line);
		ft_fprintf(1, "\n");
	}
	else
		data->exit_code = 1;
	if (line)
		add_history(line);
	if (!line)
	{
		free(line);
		safe_exit(0);
	}
	free(line);
}
