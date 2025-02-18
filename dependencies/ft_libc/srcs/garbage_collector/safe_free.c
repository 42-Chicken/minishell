/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 08:31:08 by rguigneb          #+#    #+#             */
/*   Updated: 2025/02/18 11:19:39 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garbage.h"

void	safe_free(void *pointer)
{
	int	*context;

	context = get_current_context();
	if (!context)
		return ;
	if (!delete_from_context(pointer, *context))
		return ;
	free(pointer);
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

void	free_garbage(int context)
{
	t_list	*lst;
	t_list	**garbage_head;
	void	*ptr;

	if (context < 0 || context >= CONTEXT_MAX)
		return ;
	garbage_head = get_garbage_from_context(context);
	if (!garbage_head || !*garbage_head)
		return ;
	lst = *garbage_head;
	while (lst)
	{
		ptr = lst->content;
		if (delete_from_context(ptr, context) && ptr)
			free(ptr);
		lst = *garbage_head;
	}
	*garbage_head = NULL;
}

void	free_all_contexts_garbage(void)
{
	int	context;

	context = -1;
	while (++context < CONTEXT_MAX)
		free_garbage(context);
}
