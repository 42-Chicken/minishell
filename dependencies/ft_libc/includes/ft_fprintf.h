/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 15:42:59 by rguigneb          #+#    #+#             */
/*   Updated: 2025/01/29 10:14:42 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FPRINTF_H

# include "libft.h"
# include "stdarg.h"
# include "stdio.h"

# define FT_FPRINTF_H

int		ft_fprintf(int fd, const char *format, ...);
int		ft_unsigned_putnbr(unsigned int n, int fd);
void	ft_print_hex_x(unsigned long num_hex, int pre, int fd);
void	ft_print_hex_big_x(unsigned long num_hex, int pre, int fd);

size_t	get_len_num(long n);
size_t	get_hex_len(unsigned long num, int pre);

int		handle_char(va_list args, int fd);
int		handle_str(va_list args, int fd);
int		handle_unsigned_num(va_list args, int fd);
int		handle_num(va_list args, int fd);
int		handle_hex(va_list args, int fd);
int		handle_big_hex(va_list args, int fd);
int		handle_address(va_list args, int fd);

#endif
