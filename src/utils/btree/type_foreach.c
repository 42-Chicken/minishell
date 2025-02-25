/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_foreach.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 15:30:00 by rguigneb          #+#    #+#             */
/*   Updated: 2025/02/24 11:39:11 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "binary_tree.h"

static void	btree_foreach_recursive(t_btree **head, t_btree *current,
		t_btree_node_type type, void (*func)(t_btree **, t_btree *))
{
	if (!head || !*head || !current || !func)
		return ;
	if (current->type == type)
		func(head, current);
	btree_foreach_recursive(head, current->left, type, func);
	btree_foreach_recursive(head, current->right, type, func);
}

void	btree_type_foreach(t_btree **head, t_btree_node_type type,
		void (*func)(t_btree **, t_btree *))
{
	if (!head || !*head || !func)
		return ;
	btree_foreach_recursive(head, *head, type, func);
}

static void	btree_foreach_recursive_with_other(t_btree **head, t_btree *current,
		t_btree_node_type type, void (*func)(t_btree **, t_btree *, void *),
		void *other)
{
	if (!head || !*head || !current || !func)
		return ;
	if (current->type == type)
		func(head, current, other);
	btree_foreach_recursive_with_other(head, current->left, type, func, other);
	btree_foreach_recursive_with_other(head, current->right, type, func, other);
}

void	btree_type_foreach_other(t_btree **head, t_btree_node_type type,
		void (*func)(t_btree **, t_btree *, void *), void *other)
{
	if (!head || !*head || !func)
		return ;
	btree_foreach_recursive_with_other(head, *head, type, func, other);
}
