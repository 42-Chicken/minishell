/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsigned_num.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 14:25:52 by rguigneb          #+#    #+#             */
/*   Updated: 2025/01/29 10:15:20 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fprintf.h"

int	handle_unsigned_num(va_list args, int fd)
{
	unsigned int	u;

	u = va_arg(args, unsigned int);
	ft_unsigned_putnbr(u, fd);
	return (get_len_num((long)u));
}
