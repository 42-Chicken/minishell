/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_checks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 11:46:25 by rguigneb          #+#    #+#             */
/*   Updated: 2025/03/11 15:55:47 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	recursive_check_call(t_btree **head, t_btree *node,
		t_minishell *data)
{
	if (!node || !head || data->execution_tree_error != EXECTREE_ERR_NONE)
		return ;
	if (node->type == BTREE_PIPE_TYPE)
	{
		if (!node->prev || (node->prev->type != BTREE_COMMAND_TYPE
				&& node->prev->type != BTREE_REDIRECTION_TYPE))
			data->execution_tree_error = EXECTREE_ERR_UNEXEPTED_PIPE;
		else if (!node->left)
			data->execution_tree_error = EXECTREE_ERR_UNEXEPTED_PIPE;
		else if (node->left->type == BTREE_REDIRECTION_TYPE)
		{
			if (node->left->left
				&& node->left->left->type != BTREE_COMMAND_TYPE)
				data->execution_tree_error = EXECTREE_ERR_UNEXEPTED_PIPE;
		}
	}
	else if (node->type == BTREE_AND_TYPE && (!node->left || !node->right))
		data->execution_tree_error = EXECTREE_ERR_UNEXEPTED_AND;
	else if (node->type == BTREE_OR_TYPE && (!node->left || !node->right))
		data->execution_tree_error = EXECTREE_ERR_UNEXEPTED_OR;
}

void	check_exec_tree(t_minishell *data)
{
	btree_foreach(&data->execution_tree, (void (*)(t_btree **, t_btree *,
				void *))recursive_check_call, data);
}
