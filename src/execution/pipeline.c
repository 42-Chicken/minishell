/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 08:22:24 by rguigneb          #+#    #+#             */
/*   Updated: 2025/02/17 15:59:58 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"

void	execution_pipeline(t_minishell *data)
{
	t_btree_command_node	node;
	t_command				command;

	ft_bzero(&command, sizeof(t_command));
	create_safe_memory_context();
	command.argv = safe_malloc(10000);
	command.argv[0] = ft_strdup("echo");
	node.commands[0] = ft_lstnew((void *)&command);
	node.commands[1] = ft_lstnew((void *)&command);
	data->execution_tree = btree_create_node(BTREE_OR_TYPE);
	data->execution_tree->left = btree_create_node(BTREE_COMMANDS_TYPE);
	data->execution_tree->left->content = &node;
	data->execution_tree->right = btree_create_node(BTREE_AND_TYPE);
	data->execution_tree->right->left = btree_create_node(BTREE_COMMANDS_TYPE);
	data->execution_tree->right->left->content = &node;

	if (!data || !data->execution_tree)
		return ;
	link_execution_tree_pipes(data);
	execute_binary_tree(data);
	print_execution_tree(data);
	exit_safe_memory_context();
}
