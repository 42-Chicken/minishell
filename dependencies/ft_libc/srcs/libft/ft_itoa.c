/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 19:26:01 by rguigneb          #+#    #+#             */
/*   Updated: 2025/01/27 08:56:39 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "garbadge.h"

static size_t	get_number_len(long n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n = n * -1;
		++i;
	}
	while (n > 0 && ++i)
		n /= 10;
	return (i);
}

char	*ft_itoa(int n)
{
	size_t	i;
	size_t	is_negative;
	size_t	number_len;
	long	nb;
	char	*result;

	nb = (long)n;
	i = get_number_len(nb);
	is_negative = nb < 0;
	number_len = i;
	result = (char *)MALLOC(number_len * sizeof(char) + 1);
	if (!result)
		return (NULL);
	if (is_negative)
		nb = -nb;
	while (--i < number_len)
	{
		result[i] = nb % 10 + '0';
		nb /= 10;
	}
	if (is_negative)
		result[0] = '-';
	result[number_len] = 0;
	return (result);
}
