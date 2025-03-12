/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:33:17 by rguigneb          #+#    #+#             */
/*   Updated: 2025/03/12 14:41:03 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_btree	*get_last_condition(t_list *lst, unsigned int priority)
{
	t_list	*current;

	current = NULL;
	while (lst)
	{
		if ((((t_btree *)lst->content)->type == BTREE_AND_TYPE
				|| ((t_btree *)lst->content)->type == BTREE_OR_TYPE)
			&& ((t_btree *)lst->content)->priority == priority)
			current = lst;
		lst = lst->next;
	}
	if (current)
		return (current->content);
	return (NULL);
}

void	lst_add_before_last(t_list **lst, t_list *node)
{
	t_list	*current;
	t_list	*prev;

	if (ft_lstsize(*lst) <= 1)
	{
		current = *lst;
		if (current)
			current->next = NULL;
		node->next = current;
		*lst = node;
	}
	else
	{
		current = *lst;
		prev = NULL;
		while (current && current->next)
		{
			prev = current;
			current = current->next;
		}
		if (prev)
			prev->next = node;
		node->next = current;
		current->next = NULL;
	}
}

t_list	*get_before_last(t_list *head)
{
	t_list	*current;

	current = head;
	while (current && current->next)
	{
		current = current->next;
	}
	return (current);
}
