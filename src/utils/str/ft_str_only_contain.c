/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_only_contain.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 11:39:07 by rguigneb          #+#    #+#             */
/*   Updated: 2025/02/20 11:45:30 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_str_only_contain(char *str, char *set)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (ft_isalpha(str[i]))
			continue ;
		if (!ft_strchr(set, str[i]))
			return (false);
	}
	return (true);
}
