/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 19:26:01 by rguigneb          #+#    #+#             */
/*   Updated: 2025/01/21 11:41:47 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;

	i = ft_strlen(s) - 1;
	if (i == (size_t)-1)
		i = 0;
	while (s[i] && s[i] != (unsigned char)c && (unsigned char)c != 0)
		i--;
	if (s[i] == (unsigned char)c || ((unsigned char)c == 0 && s[0] != 0))
		return ((char *)s + i + ((unsigned char)c == 0 && s[0] != 0));
	return (NULL);
}
