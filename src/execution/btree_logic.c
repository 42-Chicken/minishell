/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_logic.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 08:23:37 by rguigneb          #+#    #+#             */
/*   Updated: 2025/02/25 08:28:57 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"

void	process_and_logic(t_minishell *data, t_btree *node)
{
	if (node->left && node->left->type == BTREE_COMMAND_TYPE)
	{
		handle_commands(data, node->left);
		if (data->exit_code == 0)
			handle_commands(data, node->right);
	}
	else
		recusrive_execute_binary_tree(data, node->left);
}

void	process_or_logic(t_minishell *data, t_btree *node)
{
	if (node->left && node->left->type == BTREE_COMMAND_TYPE)
	{
		handle_commands(data, node->left);
		if (data->exit_code != 0)
			handle_commands(data, node->right);
	}
	else
		recusrive_execute_binary_tree(data, node->left);
}
