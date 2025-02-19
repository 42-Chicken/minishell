/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 11:15:06 by rguigneb          #+#    #+#             */
/*   Updated: 2025/02/17 11:27:09 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "binary_tree.h"

t_btree	*btree_create_node(t_btree_node_type type)
{
	t_btree	*node;

	node = safe_malloc(sizeof(t_btree));
	ft_bzero(node, sizeof(t_btree));
	node->type = type;
	return (node);
}
