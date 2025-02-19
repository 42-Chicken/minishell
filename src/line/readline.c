/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 19:01:37 by romain            #+#    #+#             */
/*   Updated: 2025/02/19 08:35:18 by rguigneb         ###   ########.fr       */
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
	{
		command = safe_malloc(sizeof(t_command));
		ft_bzero(command, sizeof(t_command));
		command->argv = ft_split(line, ' ');
		command->envp = (char **)data->envp;
		command->error = COMMAND_NO_ERROR;
		node = btree_create_node(BTREE_COMMANDS_TYPE);
		node->right = NULL;
		node->left = btree_create_node(BTREE_COMMANDS_CONTENT_TYPE);
		node->left->content = ft_lstnew(command);
		data->execution_tree = node;
		execution_pipeline(data);
	}
	else if ((!line || ft_strlen(line) <= 0) && data->exit_code == 0)
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
