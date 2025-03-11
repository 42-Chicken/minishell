/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   foreach.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 11:27:17 by rguigneb          #+#    #+#             */
/*   Updated: 2025/03/11 14:29:36 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "binary_tree.h"

static void	btree_foreach_recursive(t_btree **head, t_btree *current,
		void (*func)(t_btree **, t_btree *, void *), void *other)
{
	if (!head || !*head || !current || !func)
		return ;
	func(head, current, other);
	btree_foreach_recursive(head, current->left, func, other);
	btree_foreach_recursive(head, current->right, func, other);
}

void	btree_foreach(t_btree **head, void (*func)(t_btree **, t_btree *,
			void *), void *other)
{
	if (!head || !*head || !func)
		return ;
	btree_foreach_recursive(head, *head, func, other);
}
