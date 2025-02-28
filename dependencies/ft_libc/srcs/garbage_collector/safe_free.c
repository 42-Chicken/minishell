/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 08:31:08 by rguigneb          #+#    #+#             */
/*   Updated: 2025/02/28 13:46:07 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garbage.h"

void	context_safe_free(int context, void *pointer)
{
	if (context < 0 || context >= CONTEXT_MAX)
		return ;
	if (!delete_from_context(pointer, context))
		return ;
	free(pointer);
}

void	safe_free(void *pointer)
{
	int	*context;

	context = get_current_context();
	if (!context)
		return ;
	context_safe_free(*context, pointer);
}

bool	delete_pointer_from_list(t_list **head, t_list *lst, void *pointer)
{
	t_list	*prev;
	t_list	*next;
	bool	deleted;

	lst = *head;
	prev = NULL;
	deleted = false;
	while (lst)
	{
		next = lst->next;
		if (lst->content == pointer)
		{
			if (prev)
				prev->next = lst->next;
			else
				*head = lst->next;
			deleted = true;
			free(lst);
			lst = NULL;
		}
		else
			prev = lst;
		lst = next;
	}
	return (deleted);
}

bool	delete_from_context(void *pointer, int context)
{
	t_list	**garbage_head;

	if (context < 0 || context >= CONTEXT_MAX)
		return (true);
	garbage_head = get_garbage_from_context(context);
	if (!garbage_head || !*garbage_head)
		return (true);
	return (delete_pointer_from_list(garbage_head, NULL, pointer));
}
