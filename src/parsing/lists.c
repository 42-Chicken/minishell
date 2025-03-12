/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:36:00 by rguigneb          #+#    #+#             */
/*   Updated: 2025/03/12 14:41:04 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool	remain_node_for_priority(t_list *lst, unsigned int priority)
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
		return (true);
	return (false);
}

t_list	*left_truncate_lst(t_list *lst, t_btree *stop)
{
	t_list	*new_lst;

	new_lst = NULL;
	while (lst && lst->content != stop)
	{
		ft_lstadd_back(&new_lst, ft_lstnew(lst->content));
		lst = lst->next;
	}
	return (new_lst);
}

t_list	*right_truncate_lst(t_list *lst, t_btree *stop)
{
	t_list	*new_lst;

	new_lst = NULL;
	while (lst && lst->content != stop)
		lst = lst->next;
	if (lst)
		lst = lst->next;
	while (lst)
	{
		ft_lstadd_back(&new_lst, ft_lstnew(lst->content));
		lst = lst->next;
	}
	return (new_lst);
}
