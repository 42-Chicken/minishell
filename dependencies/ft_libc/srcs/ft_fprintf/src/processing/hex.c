/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 14:25:52 by rguigneb          #+#    #+#             */
/*   Updated: 2025/01/29 10:16:39 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fprintf.h"

int	handle_hex(va_list args, int fd)
{
	unsigned int	h;

	h = va_arg(args, unsigned int);
	if (h == 0)
	{
		ft_putchar_fd('0', 1);
		return (1);
	}
	ft_print_hex_x((unsigned long long)h, 0, fd);
	return (get_hex_len((unsigned long)h, 0));
}

int	handle_big_hex(va_list args, int fd)
{
	unsigned int	h;

	h = va_arg(args, unsigned int);
	if (h == 0)
	{
		ft_putchar_fd('0', 1);
		return (1);
	}
	ft_print_hex_big_x((unsigned long long)h, 0, fd);
	return (get_hex_len((unsigned long)h, 0));
}
