/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:33:17 by rguigneb          #+#    #+#             */
/*   Updated: 2025/03/13 14:18:26 by rguigneb         ###   ########.fr       */
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

	if (ft_lstsize(*lst) <= 1 || (*lst
			&& ((t_btree *)(*lst)->content)->type == BTREE_COMMAND_TYPE))
	{
		ft_lstadd_front(lst, node);
	}
	else
	{
		current = *lst;
		while (current && current->next)
		{
			if (((t_btree *)current->next->content)->type == BTREE_COMMAND_TYPE)
			{
				node->next = current->next;
				current->next = node;
				break ;
			}
			current = current->next;
		}
		if (!node->next)
			ft_lstadd_front(lst, node);
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
