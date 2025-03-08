/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_same_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 11:00:31 by rguigneb          #+#    #+#             */
/*   Updated: 2025/03/08 14:43:09 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_same_str(char *str1, char *str2)
{
	return (str1 && str2 && ft_strlen(str1) == ft_strlen(str2)
		&& ft_strncmp(str1, str2, ft_strlen(str1)) == 0);
}
