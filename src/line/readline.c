/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efranco <efranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 19:01:37 by romain            #+#    #+#             */
/*   Updated: 2025/02/19 15:26:49 by efranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"
#include "parsing.h"
#include "paths.h"

void	handle_readline(t_minishell *data)
{
	char		*line;
	t_command	*command;
	t_btree		*node;
	t_list		*lst;
	int			d;
	char		**pipes;

	line = readline(get_prompt(data));
	// if (line && ft_strncmp(line, "exit", ft_strlen("exit")) == 0)
	// {
	// 	// d = ft_split(line, ' ');
	// 	// if (d && d[0] && d[1])
	// 	// {
	// 	// 	data->exit_code = ft_atoi(d[1]);
	// 	// }
	// 	data->stop = true;
	// 	free(line);
	// 	return ;
	// }
	(void)command;
	(void)node;
	if (line && ft_strlen(line) > 0)
		data->exit_code = 0;
	else
		data->exit_code = 1;
	if (line)
	{
		add_history(line);
		parse_line(data, line);
	}
	if (!line)
	{
		ft_fprintf(STDOUT_FILENO, "\n");
		data->stop = true;
	}
	free(line);
}
