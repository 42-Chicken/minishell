/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 08:32:16 by rguigneb          #+#    #+#             */
/*   Updated: 2025/02/20 10:11:41 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garbage.h"
#include "ft_fprintf.h"

void	add_to_garbage(void *pointer, int context)
{
	t_list	**garbage_head;
	t_list	*lst;

	if (!pointer)
		return ;
	if (context < 0 || context >= CONTEXT_MAX)
		return ;
	garbage_head = get_garbage_from_context(context);
	lst = (t_list *)malloc(sizeof(t_list));
	if (!lst)
	{
		free(pointer);
		ft_fprintf(STDERR_FILENO,
			"minishell: a malloc failed during the execution,\
			heap memory has been freed entirly");
		safe_exit(EXIT_FAILURE);
	}
	lst->content = pointer;
	lst->next = NULL;
	ft_lstadd_front(garbage_head, lst);
}

void	reset_garbage(int context)
{
	t_list	**garbage_head;

	if (context < 0 || context >= CONTEXT_MAX)
		return ;
	garbage_head = get_garbage_from_context(context);
	if (!garbage_head || !*garbage_head)
		return ;
	*garbage_head = NULL;
}

void	reset_all_garbages(void)
{
	int	i;

	i = 0;
	while (i < CONTEXT_MAX)
		reset_garbage(i++);
}
