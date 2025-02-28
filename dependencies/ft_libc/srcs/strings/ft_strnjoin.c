/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 15:53:23 by rguigneb          #+#    #+#             */
/*   Updated: 2025/02/18 11:17:59 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_strings.h"
#include "garbage.h"

char	*ft_strnjoin(char const *s1, char const *s2, size_t max)
{
	size_t	i;
	size_t	k;
	size_t	total_len;
	char	*result;

	i = -1;
	k = 0;
	total_len = ft_strlen(s1) + ft_strlen(s2);
	if (total_len > max)
		total_len = ft_strlen(s1) + max;
	result = (char *)MALLOC(sizeof(char) * total_len + 1);
	if (!result)
		return (NULL);
	while (s1[++i])
		result[k++] = s1[i];
	i = -1;
	while (s2[++i] && i < max)
		result[k++] = s2[i];
	result[k] = 0;
	return (result);
}
