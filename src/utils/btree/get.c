/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 11:46:00 by rguigneb          #+#    #+#             */
/*   Updated: 2025/02/17 12:03:43 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "binary_tree.h"

t_btree	*recusrive_left_get(t_btree *node, t_btree_node_type type)
{
	if (!node)
		return (NULL);
	if (node->type == type)
		return (node);
	else
		return (recusrive_left_get(node->left, type));
}

t_btree	*recusrive_rigth_get(t_btree *node, t_btree_node_type type)
{
	if (!node)
		return (NULL);
	if (node->type == type)
		return (node);
	else
		return (recusrive_rigth_get(node->left, type));
}

t_btree	*get_first_previous(t_btree *node, t_btree_node_type type)
{
	t_btree	*current;

	if (!node)
		return (NULL);
	current = node->prev;
	while (current && current->type != type)
		current = current->prev;
	return (current);
}

