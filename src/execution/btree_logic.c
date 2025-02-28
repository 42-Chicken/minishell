/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_logic.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 08:23:37 by rguigneb          #+#    #+#             */
/*   Updated: 2025/02/28 09:24:38 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"

bool	process_and_logic(t_minishell *data, t_btree *node)
{
	recusrive_execute_binary_tree(data, node->left);
	if (data->exit_code == 0)
		recusrive_execute_binary_tree(data, node->right);
	if (data->exit_code == 0)
		return (true);
	return (false);
}

bool	process_or_logic(t_minishell *data, t_btree *node)
{
	recusrive_execute_binary_tree(data, node->left);
	if (data->exit_code != 0)
		recusrive_execute_binary_tree(data, node->right);
	else
		return (true);
	if (data->exit_code == 0)
		return (true);
	return (false);
}
