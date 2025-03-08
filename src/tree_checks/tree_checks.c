/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_checks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 11:46:25 by rguigneb          #+#    #+#             */
/*   Updated: 2025/03/08 12:00:06 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void recursive_check_call(t_btree **head, t_btree *node, t_minishell *data)
{
	if (!node || !head || data->execution_tree_error != EXECTREE_ERR_NONE)
		return ;
	if (node->type == BTREE_PIPE_TYPE)
	{
		if (!node->prev || node->prev->type != BTREE_COMMAND_TYPE)
			data->execution_tree_error = EXECTREE_ERR_UNEXEPTED_PIPE;
		else if (!node->left)
			data->execution_tree_error = EXECTREE_ERR_UNEXEPTED_PIPE;
		else if (node->left->type == BTREE_REDIRECTION_TYPE)
	}
}

bool check_exec_tree(t_minishell *data)
{
	btree_foreach(data->execution_tree, (void (*)(t_btree **, t_btree *, void *))recursive_check_call, data);
}
