/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 19:26:01 by rguigneb          #+#    #+#             */
/*   Updated: 2025/01/21 11:41:45 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	k;

	i = -1;
	if (little[0] == 0)
		return ((char *)big);
	while (++i <= len && big[i])
	{
		k = 0;
		while (
			big[k + i]
			&& little[k]
			&& big[k + i] == little[k]
			&& k + i < len
		)
			k++;
		if (little[k] == 0)
			return ((char *)big + i);
	}
	return (NULL);
}
