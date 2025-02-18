/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 14:10:18 by rguigneb          #+#    #+#             */
/*   Updated: 2025/02/18 11:16:46 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GARBAGE_H
# define GARBAGE_H

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
void	free_garbage(int context);
void	safe_free(void *pointer);
void	add_to_garbage(void *pointer, int context);
t_list	**get_garbage_from_context(int context);
void	reset_garbage(int context);
int		*get_current_context(void);
void	create_safe_memory_context(void);
void	exit_safe_memory_context(void);
bool	delete_from_context(void *pointer, int context);
void	reset_all_garbages(void);
void	send_pointer_to_upper_context(void *ptr);
void	send_pointer_to_main_context(void *pointer);

void	free_all_contexts_garbage(void);

#endif
