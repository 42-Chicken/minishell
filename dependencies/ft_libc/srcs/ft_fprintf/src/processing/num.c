/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   num.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 14:25:52 by rguigneb          #+#    #+#             */
/*   Updated: 2025/01/29 10:15:20 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fprintf.h"

int	handle_num(va_list args, int fd)
{
	int	n;

	n = va_arg(args, int);
	ft_putnbr_fd(n, fd);
	return (get_len_num((long)n));
}
