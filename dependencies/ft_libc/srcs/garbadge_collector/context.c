/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   context.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:11:51 by rguigneb          #+#    #+#             */
/*   Updated: 2025/02/18 10:47:31 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garbadge.h"

int	*get_current_context(void)
{
	static int	context = 0;

	if (context < 0)
		context = 0;
	else if (context >= CONTEXT_MAX)
		context = CONTEXT_MAX - 1;
	return (&context);
}

void	create_safe_memory_context(void)
{
	int	*context;

	context = get_current_context();
	if (!context)
		return ;
	if (*context < CONTEXT_MAX - 1)
		(*context)++;
}

void	exit_safe_memory_context(void)
{
	int	*context;

	context = get_current_context();
	if (!context)
		return ;
	free_garbadge(*context);
	if (*context > 0)
		(*context)--;
}

void	send_pointer_to_upper_context(void *ptr)
{
	int	*context;

	if (!ptr)
		return ;
	context = get_current_context();
	if (!context)
		return ;
	if (*context > 0)
	{
		add_to_garbadge(ptr, *context - 1);
		delete_from_context(ptr, *context);
	}
}

void	send_pointer_to_main_context(void *ptr)
{
	int	*context;

	if (!ptr)
		return ;
	context = get_current_context();
	if (!context)
		return ;
	if (*context > 0)
	{
		add_to_garbadge(ptr, 0);
		delete_from_context(ptr, *context);
	}
}
