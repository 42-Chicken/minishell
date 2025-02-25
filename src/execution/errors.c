/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 13:07:17 by rguigneb          #+#    #+#             */
/*   Updated: 2025/02/25 09:12:21 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "define.h"
#include "execution.h"
#include "minishell.h"

static void	print_redirections_errors(t_btree *node)
{
	const char			*error;
	t_btree_redir_node	*redir;

	redir = (t_btree_redir_node *)node->content;
	if (redir->error == REDIRECTION_NO_ERROR)
		return ;
	if (redir->error == REDIRECTION_NO_SUCH_FILE_OR_DIRECTORY)
		error = ERROR_NO_SUCH_FILE_OR_DIRECTORY;
	if (redir->error == REDIRECTION_HERE_DOC_NO_SUCH_FILE_OR_DIRECTORY)
		error = ERROR_HEREDOC_FILE_DELETED;
	if (redir->error == REDIRECTION_HERE_DOC_PERMISSION_DENIED)
		error = ERROR_HEREDOC_FILE_PERMISSION_DENIED;
	if (redir->error == REDIRECTION_PERMISSION_DENIED)
		error = ERROR_PERMISSION_DENIED;
	if (redir->error == REDIRECTION_ERROR_OPENING_FILE)
		error = ERROR_CANNOT_OPEN_FILE;
	if (error)
		ft_fprintf(STDERR_FILENO, error, redir->file);
}

static void	print_commands_errors(t_btree *node)
{
	const char	*error;
	t_command	*command;

	command = (t_command *)node->content;
	if (command->error == COMMAND_NO_ERROR)
		return ;
	if (command->error == COMMAND_NOT_FOUND_ERROR)
		error = COMMAND_NOT_FOUND;
	if (command->error == COMMAND_NO_SUCH_FILE_OR_DIRECTORY_ERROR)
		error = ERROR_NO_SUCH_FILE_OR_DIRECTORY;
	if (command->error == COMMAND_IS_SUCH_FILE_OR_DIRECTORY_ERROR)
		error = IS_DIRECTORY_PATH;
	if (command->error == COMMAND_PERMISSION_DENIED_ERROR)
		error = ERROR_NO_SUCH_FILE_OR_DIRECTORY;
	if (command->error == COMMAND_ARGUMENT_REQUIRED_ERROR)
		error = COMMAND_ARGUMENTS;
	if (error)
		ft_fprintf(STDERR_FILENO, error, command->argv[0]);
}

static void	print_tree_errors_recusive(t_btree **head, t_btree *node,
		void *data)
{
	(void)data;
	(void)head;
	if (node->type == BTREE_COMMAND_TYPE)
		print_commands_errors(node);
	if (node->type == BTREE_REDIRECTION_TYPE)
		print_redirections_errors(node);
}

void	print_tree_errors(t_minishell *data)
{
	btree_foreach(&data->execution_tree, print_tree_errors_recusive, data);
}
