/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 08:22:24 by rguigneb          #+#    #+#             */
/*   Updated: 2025/02/19 13:02:23 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"

void	execution_pipeline(t_minishell *data)
{
	// t_list		*node;
	// t_command	command;
	// t_command	command2;

	create_safe_memory_context();
	// ft_bzero(&command, sizeof(t_command));
	// command.argv = safe_malloc(10000);
	// command.error = COMMAND_NO_ERROR;
	// command.argv[0] = ft_strdup("echo");
	// command.argv[1] = ft_strdup("-l fwqfqw fwqfq fqwf qfq fqwf qfwf qwf qfwf qfqwf qwfq");
	// command.argv[2] = NULL;
	// command.envp = (char **)data->envp;
	// ft_bzero(&command2, sizeof(t_command));
	// command2.argv = safe_malloc(10000);
	// command2.error = COMMAND_NO_ERROR;
	// command2.argv[0] = ft_strdup("env");
	// // command2.argv[1] = ft_strdup("-e");
	// command2.argv[1] = NULL;
	// command2.envp = (char **)data->envp;
	// node = ft_lstnew((void *)&command);
	// // ft_lstadd_back(&node, ft_lstnew((void *)&command));
	// ft_lstadd_back(&node, ft_lstnew((void *)&command2));
	// data->execution_tree = btree_create_node(BTREE_AND_TYPE);
	// data->execution_tree->left = btree_create_node(BTREE_COMMANDS_TYPE);
	// data->execution_tree->left->prev = data->execution_tree;
	// data->execution_tree->left->content = NULL;
	// data->execution_tree->left->left = btree_create_node(BTREE_COMMANDS_CONTENT_TYPE);
	// data->execution_tree->left->left->prev = data->execution_tree->left;
	// data->execution_tree->left->left->content = node;
	// data->execution_tree->left->right = btree_create_node(BTREE_COMMANDS_CONTENT_TYPE);
	// data->execution_tree->left->right->prev = data->execution_tree->left;
	// data->execution_tree->left->right->content = node;
	// data->execution_tree->right = btree_create_node(BTREE_AND_TYPE);
	// data->execution_tree->right->prev = data->execution_tree->right;
	// data->execution_tree->right->left = btree_create_node(BTREE_COMMANDS_TYPE);
	// data->execution_tree->right->left->prev = data->execution_tree->right;
	// data->execution_tree->right->left->left = btree_create_node(BTREE_COMMANDS_CONTENT_TYPE);
	// data->execution_tree->right->left->left->content = node;
	// data->execution_tree->right->left->left->prev = data->execution_tree->right->left;
	// data->execution_tree->right->left->right = btree_create_node(BTREE_COMMANDS_CONTENT_TYPE);
	// data->execution_tree->right->left->right->prev = data->execution_tree->right->left;
	// data->execution_tree->right->left->right->content = node;
	if (!data || !data->execution_tree)
		return ;
	execute_binary_tree(data);
	// print_execution_tree(data);
	exit_safe_memory_context();
}
