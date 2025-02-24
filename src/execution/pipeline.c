/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 08:22:24 by rguigneb          #+#    #+#             */
/*   Updated: 2025/02/24 11:16:43 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"

void	execution_pipeline(t_minishell *data)
{
	if (!data || !data->execution_tree)
		return ;
	create_safe_memory_context();
	save_heredocs_tmp_files(data);
	bind_commands_to_executable(data);
	bind_redirections_to_fds(data);
	print_tree_errors(data);
	execute_binary_tree(data);
	print_execution_tree(data);
	delete_heredocs_tmp_files(data);
	exit_safe_memory_context();
}
