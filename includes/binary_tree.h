/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_tree.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 10:47:33 by rguigneb          #+#    #+#             */
/*   Updated: 2025/02/19 14:12:29 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BINARY_TREE_H
# define BINARY_TREE_H

# include "execution.h"
# include <stdlib.h>

typedef enum e_btree_node_type
{
	BTREE_NONE_TYPE = -1,
	BTREE_REDIRECTION_TYPE,
	BTREE_COMMAND_TYPE,
	BTREE_PIPE_TYPE,
	BTREE_OR_TYPE,
	BTREE_AND_TYPE
}						t_btree_node_type;

typedef struct s_btree
{
	void				*content;
	t_btree_node_type	type;
	struct s_btree		*left;
	struct s_btree		*right;
	struct s_btree		*prev;
}						t_btree;

// ---------------------------------
//
// UTILS
//
// ---------------------------------
void					btree_foreach(t_btree **head, void (*func)(t_btree **,
								t_btree *, void *), void *other);
t_btree					*btree_create_node(t_btree_node_type type);
t_btree					*get_first_previous(t_btree *node,
							t_btree_node_type type);
t_btree					*recusrive_left_get(t_btree *node,
							t_btree_node_type type);
t_btree					*recusrive_rigth_get(t_btree *node,
							t_btree_node_type type);

#endif
