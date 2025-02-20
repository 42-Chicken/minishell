/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 19:01:37 by romain            #+#    #+#             */
/*   Updated: 2025/02/20 09:04:09 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"
#include "parsing.h"
#include "paths.h"

void	handle_readline(t_minishell *data)
{
	char						*line;
	t_command					*command;
	t_btree						*node;
	t_btree						*prev;
	int							d;
	char						**pipes;
	t_btree_redirection_node	*redir;

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
	data->execution_tree = NULL;
	if (line && ft_strlen(line) > 0)
	{
		d = 0;
		pipes = ft_split(line, '|');
		data->execution_tree = btree_create_node(BTREE_REDIRECTION_TYPE);
		redir = safe_malloc(sizeof(t_btree_redirection_node));
		redir->type = REDIRECTION_IN_TYPE;
		redir->fd = open("test", O_RDONLY);
		data->execution_tree->content = redir;
		prev = data->execution_tree;
		// data->execution_tree->prev = node;
		while (pipes[d])
		{
			node = btree_create_node(BTREE_COMMAND_TYPE);
			if (!data->execution_tree)
			{
				data->execution_tree = node;
				prev = node;
			}
			else
			{
				prev->left = node;
				prev = node;
			}
			command = safe_malloc(sizeof(t_command));
			ft_bzero(command, sizeof(t_command));
			command->argv = ft_split(pipes[d], ' ');
			command->envp = (char **)data->envp;
			command->error = COMMAND_NO_ERROR;
			command->out_pipe = (t_pipe){PIPE_NO_VALUE, STDOUT_FILENO};
			command->in_pipe = (t_pipe){PIPE_NO_VALUE, PIPE_NO_VALUE};
			node->content = (void *)command;
			if (pipes[d + 1])
			{
				node = btree_create_node(BTREE_PIPE_TYPE);
				prev->left = node;
				node->prev = prev;
				prev = node;
			}
			d++;
		}
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
