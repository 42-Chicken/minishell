/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   address.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 14:25:52 by rguigneb          #+#    #+#             */
/*   Updated: 2025/01/29 10:15:20 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fprintf.h"

int	handle_address(va_list args, int fd)
{
	unsigned long	h;

	h = va_arg(args, unsigned long);
	if (!h)
	{
		ft_putstr_fd("(nil)", fd);
		return (5);
	}
	ft_print_hex_x((unsigned long long)h, 1, fd);
	return (get_hex_len(h, 1));
}
