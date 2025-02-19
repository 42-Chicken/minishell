/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 19:01:37 by romain            #+#    #+#             */
/*   Updated: 2025/02/19 14:13:05 by rguigneb         ###   ########.fr       */
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
	{
		d = 0;
		pipes = ft_split(line, '|');
		node = btree_create_node(BTREE_COMMAND_TYPE);
		node->right = NULL;
		while (pipes[d])
		{
			command = safe_malloc(sizeof(t_command));
			lst = ft_lstnew(command);
			if (!node->left->content)
				node->left->content = lst;
			else
				ft_lstadd_back((t_list **)&node->left->content, lst);
			ft_bzero(command, sizeof(t_command));
			command->argv = ft_split(pipes[d], ' ');
			command->envp = (char **)data->envp;
			command->error = COMMAND_NO_ERROR;
			d++;
		}
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
