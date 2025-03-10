/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 08:22:24 by rguigneb          #+#    #+#             */
/*   Updated: 2025/03/10 15:40:22 by rguigneb         ###   ########.fr       */
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

void	execution_pipeline(t_minishell *data)
{
	if (!data || !data->execution_tree)
		return ;
	create_safe_memory_context();
	save_heredocs_tmp_files(data);
	bind_commands_to_executable(data);
	bind_redirections_to_fds(data);
	check_exec_tree(data);
	if (data->execution_tree_error == EXECTREE_ERR_NONE)
	{
		print_tree_errors(data);
		execute_binary_tree(data);
		print_execution_tree(data);
		delete_heredocs_tmp_files(data);
	}
	else
		print_error(data);
	exit_safe_memory_context();
}
