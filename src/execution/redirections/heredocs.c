/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 09:00:26 by rguigneb          #+#    #+#             */
/*   Updated: 2025/02/24 15:13:50 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "signals.h"

#define HEREDOC_WARNING "\nminishell: warning: here-document at %d delimited by \
end-of-file (wanted `EOF')\n"

static void	fill_file(t_minishell *data, int fd, char *limiter)
{
	char	*line;
	int		line_count;
	int		new;

	line_count = 1;
	new = dup(STDIN_FILENO);
	while (g_sig == 0)
	{
		ft_fprintf(STDOUT_FILENO, "> ");
		line = get_next_line(new);
		if (g_sig != 0)
			break ;
		if (!line)
		{
			ft_fprintf(STDERR_FILENO, HEREDOC_WARNING, data->line_count);
			break ;
		}
		if (ft_strlen(line) > 1 && ft_strncmp(line, limiter, ft_strlen(line)
				- 1) == 0)
			break ;
		write(fd, line, ft_strlen(line));
		line_count++;
	}
	data->line_count += line_count;
	close(new);
}

static void	handle_heredocs_save(t_btree **head, t_btree *node, void *other)
{
	static int			id = 0;
	int					fd;
	t_btree_redir_node	*redir;
	t_minishell			*data;
	int					d;

	(void)head;
	data = (t_minishell *)other;
	redir = (t_btree_redir_node *)node->content;
	if (!redir || redir->type != REDIRECTION_HERE_DOC_TYPE)
		return ;
	redir->file = ft_strjoin("/tmp/minishell_heredoc_", ft_itoa(id++));
	fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_fprintf(STDERR_FILENO, "ERROR at creating heredoc in file");
		return ;
	}
	create_safe_memory_context();
	switch_to_heredoc_mode();
	fill_file(data, fd, redir->limiter);
	reset_signals(true);
	exit_safe_memory_context();
	close(fd);
}

static void	handle_heredocs_unlink(t_btree **head, t_btree *node)
{
	t_btree_redir_node	*redir;

	(void)head;
	redir = (t_btree_redir_node *)node->content;
	if (!redir || redir->type != REDIRECTION_HERE_DOC_TYPE || !redir->file)
		return ;
	unlink(redir->file);
}

void	save_heredocs_tmp_files(t_minishell *data)
{
	btree_type_foreach_other(&data->execution_tree, BTREE_REDIRECTION_TYPE,
		handle_heredocs_save, data);
}

void	delete_heredocs_tmp_files(t_minishell *data)
{
	btree_type_foreach(&data->execution_tree, BTREE_REDIRECTION_TYPE,
		handle_heredocs_unlink);
}
