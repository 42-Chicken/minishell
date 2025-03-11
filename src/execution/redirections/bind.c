/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bind.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 15:51:08 by rguigneb          #+#    #+#             */
/*   Updated: 2025/03/11 15:28:34 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"
#include "paths.h"

static void	open_in_redir_fd(t_btree_redir_node *redir)
{
	if (access(redir->file, F_OK) == -1)
	{
		if (redir->type == REDIRECTION_IN_TYPE)
			redir->error = REDIRECTION_NO_SUCH_FILE_OR_DIRECTORY;
		else if (redir->type == REDIRECTION_HERE_DOC_TYPE)
			redir->error = REDIRECTION_HERE_DOC_NO_SUCH_FILE_OR_DIRECTORY;
	}
	else if (access(redir->file, R_OK) == -1)
	{
		if (redir->type == REDIRECTION_IN_TYPE)
			redir->error = REDIRECTION_PERMISSION_DENIED;
		else if (redir->type == REDIRECTION_HERE_DOC_TYPE)
			redir->error = REDIRECTION_HERE_DOC_PERMISSION_DENIED;
	}
	else
		redir->fd = open(redir->file, O_RDONLY);
}

static void	open_out_redir_fd(t_btree_redir_node *redir)
{
	if (redir->doubled)
		redir->fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		redir->fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
}

static void	bind_redirections(t_btree **head, t_btree *node)
{
	t_btree_redir_node	*redir;

	(void)head;
	redir = (t_btree_redir_node *)node->content;
	if (!redir || redir->error != REDIRECTION_NO_ERROR)
		return ;
	if ((redir->type == REDIRECTION_IN_TYPE
			|| redir->type == REDIRECTION_OUT_TYPE) && !redir->file)
	{
		redir->error = REDIRECTION_UNEXPETED_TOKEN;
		return ;
	}
	if (redir->type == REDIRECTION_IN_TYPE)
		open_in_redir_fd(redir);
	else if (redir->type == REDIRECTION_HERE_DOC_TYPE)
		open_in_redir_fd(redir);
	else if (redir->type == REDIRECTION_OUT_TYPE)
		open_out_redir_fd(redir);
	if (redir->fd == -1)
		redir->error = REDIRECTION_ERROR_OPENING_FILE;
}

void	bind_redirections_to_fds(t_minishell *data)
{
	btree_type_foreach(&data->execution_tree, BTREE_REDIRECTION_TYPE,
		bind_redirections);
}
