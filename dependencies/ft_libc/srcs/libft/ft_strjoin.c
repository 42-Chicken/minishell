/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 19:26:01 by rguigneb          #+#    #+#             */
/*   Updated: 2025/02/18 11:17:59 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "garbage.h"

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
