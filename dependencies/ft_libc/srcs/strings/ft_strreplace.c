/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strreplace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 09:06:24 by rguigneb          #+#    #+#             */
/*   Updated: 2025/02/12 16:20:44 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_strings.h"
#include <stdio.h>

static int	get_next_cmp_index(char *str, char *mask, int i)
{
	int	k;

	k = 0;
	while (str[i + k] && ft_strncmp(str + i + k, mask, ft_strlen(mask)) != 0)
		k++;
	return (k);
}

char	*ft_strreplace(char *str, char *mask, char *value)
{
	char	*result;
	size_t	i;

	i = 0;
	result = ft_strdup("");
	if (!str)
		return (NULL);
	if (!mask || !mask[0] || !value)
		return (ft_strdup(str));
	while (str[i])
	{
		if (ft_strncmp(str + i, mask, ft_strlen(mask)) == 0)
		{
			result = ft_strjoin(result, value);
			i += ft_strlen(mask);
		}
		else
		{
			result = ft_strnjoin(result, str + i, get_next_cmp_index(str, mask,
						i));
			i += get_next_cmp_index(str, mask, i);
		}
	}
	return (result);
}
