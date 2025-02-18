/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbadge.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 14:55:20 by rguigneb          #+#    #+#             */
/*   Updated: 2025/02/18 10:34:03 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garbadge.h"

t_list	**get_garbage_from_context(int context)
{
	static t_list	*collector[CONTEXT_MAX];

	if (context < 0 || context >= CONTEXT_MAX)
		return (NULL);
	return (&collector[context]);
}
