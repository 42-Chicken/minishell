/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbadge.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 14:10:18 by rguigneb          #+#    #+#             */
/*   Updated: 2025/02/14 10:43:00 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GARBADGE_H
# define GARBADGE_H

# include "libft.h"
# include <stdbool.h>
# include <stddef.h>
# include <stdlib.h>

# ifndef MALLOC
#  define MALLOC
# endif

# define CONTEXT_MAX 255

/******************************************************************************/

void	*safe_malloc(size_t size);
void	safe_exit(int exit_code);
void	free_garbadge(int context);
void	safe_free(void *pointer);
void	add_to_garbadge(void *pointer, int context);
t_list	**get_garbage_from_context(int context);
void	reset_garbadge(int context);
int		*get_current_context(void);
void	create_safe_memory_context(void);
void	exit_safe_memory_context(void);
void	send_pointer_to_upper_context(void *ptr);
bool	delete_from_context(void *pointer, int context);

void	free_all_contexts_garbadge(void);

#endif
