/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 19:01:37 by romain            #+#    #+#             */
/*   Updated: 2025/03/11 12:20:04 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"
#include "parsing.h"
#include "paths.h"

void	handle_readline(t_minishell *data)
{
	char	*line;

	line = readline(get_prompt(data));
	if (line && ft_strlen(line) > 0)
		add_history(line);
	data->exit_code = 0;
	data->execution_tree_error = EXECTREE_ERR_NONE;
	data->execution_tree = NULL;
	if (line && ft_strlen(line) > 0)
	{
		data->current_line = line;
		parse_line(data, line);
		execution_pipeline(data);
	}
	if (!line)
	{
		ft_fprintf(STDOUT_FILENO, "\n");
		data->stop = true;
	}
	safe_free(line);
}
