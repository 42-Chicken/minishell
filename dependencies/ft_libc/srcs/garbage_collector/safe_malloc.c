/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_malloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 08:31:08 by rguigneb          #+#    #+#             */
/*   Updated: 2025/02/20 10:11:11 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garbage.h"
#include "ft_fprintf.h"

void	*safe_malloc(size_t size)
{
	void	*memory;
	int		*context;

	memory = malloc(size);
	if (!memory)
	{
		ft_fprintf(STDERR_FILENO,
			"minishell: a malloc failed during the execution,\
			heap memory has been freed entirly");
		safe_exit(EXIT_FAILURE);
	}
	context = get_current_context();
	if (!context)
	{
		ft_fprintf(STDERR_FILENO,
			"minishell: garbadge collector context pointer doesn't exit,\
			heap memory has been freed entirly");
		safe_exit(EXIT_FAILURE);
	}
	add_to_garbage(memory, *context);
	return (memory);
}
