/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 19:01:37 by romain            #+#    #+#             */
/*   Updated: 2025/03/13 16:57:14 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"
#include "parsing.h"
#include "paths.h"

void	handle_readline(t_minishell *data)
{
	char	*line;
	char	*expanded;

	line = readline(get_prompt(data));
	expanded = expand(data, line);
	if (expanded && ft_strlen(expanded) > 0)
	{
		data->execution_tree_error = EXECTREE_ERR_NONE;
		data->exit_code = 0;
		add_history(line);
	}
	line = expanded;
	data->execution_tree_error = EXECTREE_ERR_NONE;
	data->execution_tree = NULL;
	if (line && ft_strlen(line) > 0)
	{
		data->current_line = line;
		parse_line(data, line);
		execution_pipeline(data);
	}
	if (!line)
		return (ft_fprintf(STDOUT_FILENO, "exit\n"), data->stop = true,
			(void)0);
	safe_free(line);
}
