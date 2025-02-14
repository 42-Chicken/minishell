/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 19:26:01 by rguigneb          #+#    #+#             */
/*   Updated: 2025/01/27 08:56:57 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "garbadge.h"

char	*ft_strdup(const char *s)
{
	size_t	i;
	char	*result;

	i = -1;
	result = (char *)MALLOC(ft_strlen(s) + 1);
	if (!result)
		return (NULL);
	while (s[++i])
		result[i] = s[i];
	result[i] = '\0';
	return (result);
}
