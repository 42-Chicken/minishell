/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 08:22:24 by rguigneb          #+#    #+#             */
/*   Updated: 2025/03/13 16:26:31 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "define.h"
#include "execution.h"
#include "minishell.h"
#include "signals.h"

static void	print_error(t_minishell *data)
{
	if (data->execution_tree_error == EXECTREE_ERR_UNEXEPTED_AND)
		ft_fprintf(STDERR_FILENO, ERROR_TREE_AND);
	else if (data->execution_tree_error == EXECTREE_ERR_UNEXEPTED_OR)
		ft_fprintf(STDERR_FILENO, ERROR_TREE_OR);
	else if (data->execution_tree_error == EXECTREE_ERR_UNEXEPTED_PIPE)
		ft_fprintf(STDERR_FILENO, ERROR_TREE_PIPE);
}
// else if (data->execution_tree_error == EXECTREE_ERR_UNEXPETED_TOKEN)
// 	ft_fprintf(STDERR_FILENO, ERROR_UNEXPTED_TOKEN_NEW_LINE);

void	execution_pipeline(t_minishell *data)
{
	if (!data || !data->execution_tree)
		return ;
	create_safe_memory_context();
	check_exec_tree(data);
	save_heredocs_tmp_files(data);
	link_commands_and_redirections_together(data);
	if (data->execution_tree_error == EXECTREE_ERR_NONE)
	{
		bind_commands_to_executable(data);
		bind_redirections_to_fds(data);
		print_tree_errors(data, data->execution_tree);
	}
	if (data->execution_tree_error == EXECTREE_ERR_NONE && data->exit_code == 0)
	{
		execute_binary_tree(data);
		print_execution_tree(data);
	}
	else
	{
		print_error(data);
		if (data->exit_code == 0)
			data->exit_code = 1;
	}
	delete_heredocs_tmp_files(data);
	exit_safe_memory_context();
}
