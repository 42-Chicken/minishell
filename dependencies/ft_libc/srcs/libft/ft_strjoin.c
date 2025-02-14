/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 19:26:01 by rguigneb          #+#    #+#             */
/*   Updated: 2025/01/27 08:57:09 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "garbadge.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	k;
	size_t	total_len;
	char	*result;

	i = -1;
	k = 0;
	total_len = ft_strlen(s1) + ft_strlen(s2) + 1;
	result = (char *)MALLOC(sizeof(char) * total_len);
	if (!result)
		return (NULL);
	while (s1[++i])
		result[k++] = s1[i];
	i = -1;
	while (s2[++i])
		result[k++] = s2[i];
	result[k] = 0;
	return (result);
}
