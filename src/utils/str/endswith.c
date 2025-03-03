/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   endswith.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 17:55:16 by rguigneb          #+#    #+#             */
/*   Updated: 2025/03/03 09:12:50 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	endswith(char *str, char *substr)
{
	int	i;
	int	k;
	int	sub_len;
	int	str_len;

	if (!str)
		return (0);
	if (!substr)
		return (1);
	sub_len = ft_strlen(substr);
	str_len = ft_strlen(str);
	i = str_len - 1;
	while (str[i] && str_len - i <= sub_len)
	{
		k = 0;
		while (str[i + k] && str[i + k] == substr[k])
			k++;
		if (substr[k] == 0)
			return (1);
		i--;
	}
	return (0);
}
