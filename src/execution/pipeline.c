/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 08:22:24 by rguigneb          #+#    #+#             */
/*   Updated: 2025/02/20 17:23:34 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"

void	execution_pipeline(t_minishell *data)
{
	if (!data || !data->execution_tree)
		return ;
	create_safe_memory_context();
	bind_commands_to_executable(data);
	bind_redirections_to_fds(data);
	print_tree_errors(data->execution_tree);
	execute_binary_tree(data);
	print_execution_tree(data);
	exit_safe_memory_context();
}
