/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:50:23 by rguigneb          #+#    #+#             */
/*   Updated: 2025/03/12 15:01:05 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_command	*create_command(char **argv, unsigned int priority)
{
	t_command	*command;

	command = safe_malloc(sizeof(t_command));
	ft_bzero(command, sizeof(t_command));
	command->argv = argv;
	command->priority = priority;
	return (command);
}

static void	recurisive_call(t_btree *node, t_list *remaning_nodes,
		unsigned int priority)
{
	node->right = create_final_tree(right_truncate_lst(remaning_nodes, node),
			priority);
	if (node->right)
		node->right->prev = node;
	node->left = create_final_tree(left_truncate_lst(remaning_nodes, node),
			priority);
	if (node->left)
		node->left->prev = node;
}

t_btree	*create_final_tree(t_list *remaning_nodes, unsigned int priority)
{
	t_btree	*node;

	if (!remaning_nodes)
		return (NULL);
	if (!remain_node_for_priority(remaning_nodes, priority))
		priority++;
	node = get_last_condition(remaning_nodes, priority);
	if (!node)
	{
		node = remaning_nodes->content;
		node->left = create_final_tree(remaning_nodes->next, priority);
		if (node->left)
			node->left->prev = node;
	}
	else
		recurisive_call(node, remaning_nodes, priority);
	return (node);
}
