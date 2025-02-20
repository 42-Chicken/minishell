/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 13:07:17 by rguigneb          #+#    #+#             */
/*   Updated: 2025/02/20 14:30:54 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"

static void	print_redirections_errors(t_btree *node)
{
	const char					*error;
	t_btree_redirection_node	*redir;

	redir = (t_btree_redirection_node *)node->content;
	if (redir->error == REDIRECTION_NO_ERROR)
		return ;
	if (redir->error == REDIRECTION_NO_SUCH_FILE_OR_DIRECTORY)
		error = "minishell: %s: No such file or directory\n";
	if (redir->error == REDIRECTION_PERMISSION_DENIED)
		error = "minishell: %s: Permission denied\n";
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
	if (command->error == COMMAND_NOT_FOUND)
		error = "%s: command not found\n";
	if (command->error == COMMAND_NO_SUCH_FILE_OR_DIRECTORY)
		error = "minishell: %s: No such file or directory\n";
	if (command->error == COMMAND_IS_SUCH_FILE_OR_DIRECTORY)
		error = "minishell: %s: Is a directory\n";
	if (command->error == COMMAND_PERMISSION_DENIED)
		error = "minishell: %s: Permission denied\n";
	if (error)
		ft_fprintf(STDERR_FILENO, error, command->argv[0]);
}

void	print_tree_errors(t_btree *node)
{
	if (!node)
		return ;
	if (node->type == BTREE_COMMAND_TYPE)
		print_commands_errors(node);
	if (node->type == BTREE_REDIRECTION_TYPE)
		print_redirections_errors(node);
}
