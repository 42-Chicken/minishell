/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strings.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 15:03:54 by rguigneb          #+#    #+#             */
/*   Updated: 2025/03/12 13:07:27 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STRINGS_H
# define FT_STRINGS_H

# include "garbage.h"
# include <stdbool.h>
# include <stdlib.h>

bool	ft_isspace(int c);
char	*ft_strreplace(char *str, char *mask, char *value);
char	*ft_strnjoin(char const *s1, char const *s2, size_t max);
char	*ft_strreplace_at_index(char *str, int index, int max, char *value);
int		get_next_cmp_index(char *str, char *mask, int i);

#endif
