/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 14:55:20 by rguigneb          #+#    #+#             */
/*   Updated: 2025/02/18 10:34:03 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garbage.h"

t_list	**get_garbage_from_context(int context)
{
	static t_list	*collector[CONTEXT_MAX];

	if (context < 0 || context >= CONTEXT_MAX)
		return (NULL);
	return (&collector[context]);
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
