/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 13:07:17 by rguigneb          #+#    #+#             */
/*   Updated: 2025/03/13 14:35:53 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "define.h"
#include "execution.h"
#include "minishell.h"

static void	print_error(t_btree *node, t_btree_redir_node *redir,
		const char *error)
{
	(void)node;
	// if (redir->type == REDIRECTION_IN_TYPE && recusrive_left_get(node,
	// 		BTREE_COMMAND_TYPE) && ((t_command *)recusrive_left_get(node,
	// 			BTREE_COMMAND_TYPE))->redir_error_printed == false)
	// 	ft_fprintf(STDERR_FILENO, error, redir->file);
	// if (redir->type == REDIRECTION_IN_TYPE && recusrive_prev_get(node,
	// 		BTREE_COMMAND_TYPE) && ((t_command *)recusrive_prev_get(node,
	// 			BTREE_COMMAND_TYPE))->redir_error_printed == false)
	ft_fprintf(STDERR_FILENO, error, redir->file);
}

static void	print_redirections_errors(t_minishell *data, t_btree *node)
{
	const char			*error;
	t_btree_redir_node	*redir;

	redir = (t_btree_redir_node *)node->content;
	if (redir->command && redir->command->redir_error_printed)
		return ;
	// printf("command : %p\n\n", redir->command);
	if (redir->type == REDIRECTION_OUT_TYPE && !recusrive_prev_get(node,
			BTREE_COMMAND_TYPE) && redir->file && ft_strncmp(redir->file,
			expand(data, "*"), 5) == 0)
	{
		data->execution_tree_error = EXECTREE_ERR_CANCEL;
		if (data->exit_code == 0)
			data->exit_code = 1;
		ft_fprintf(STDOUT_FILENO, ERROR_SYNTAX_AMBIGUOUS_REDIR);
		return ;
	}
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
	if (redir->error == REDIRECTION_UNEXPETED_TOKEN)
		error = ERROR_UNEXPTED_TOKEN_NEW_LINE;
	if (error)
	{
		print_error(node, redir, error);
		if (redir->command)
			redir->command->redir_error_printed = true;
		else if (!redir->command && data->exit_code == 0)
			data->exit_code = 1;
	}
}

static void	print_commands_errors(t_minishell *data, t_btree *node)
{
	const char	*error;
	t_command	*command;

	(void)data;
	command = (t_command *)node->content;
	if (is_built_in_command(command) || command->error == COMMAND_NO_ERROR)
		return ;
	if (command->error == COMMAND_NOT_FOUND_ERROR)
		error = COMMAND_NOT_FOUND;
	if (command->error == COMMAND_NO_SUCH_FILE_OR_DIRECTORY_ERROR)
		error = ERROR_NO_SUCH_FILE_OR_DIRECTORY;
	if (command->error == COMMAND_IS_SUCH_FILE_OR_DIRECTORY_ERROR)
		error = IS_DIRECTORY_PATH;
	if (command->error == COMMAND_PERMISSION_DENIED_ERROR)
		error = ERROR_PERMISSION_DENIED;
	if (command->error == COMMAND_ARGUMENT_REQUIRED_ERROR)
		error = ERROR_COMMAND_ARGUMENTS;
	if (error)
	{
		ft_fprintf(STDERR_FILENO, error, command->argv[0]);
	}
}

void	print_tree_errors(t_minishell *data, t_btree *node)
{
	if (!node)
		return ;
	if (node->type == BTREE_COMMAND_TYPE)
		print_commands_errors(data, node);
	else if (node->type == BTREE_REDIRECTION_TYPE)
		print_redirections_errors(data, node);
	print_tree_errors(data, node->left);
	print_tree_errors(data, node->right);
}
