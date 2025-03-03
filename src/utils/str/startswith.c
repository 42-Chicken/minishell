/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   startswith.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 17:55:16 by rguigneb          #+#    #+#             */
/*   Updated: 2025/03/03 09:14:08 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	startswith(char *str, char *substr)
{
	int	i;
	int	k;
	int	sub_len;

	if (!str)
		return (0);
	if (!substr)
		return (1);
	sub_len = ft_strlen(substr);
	i = 0;
	while (str[i] && i < sub_len)
	{
		k = 0;
		while (str[i + k] && str[i + k] == substr[k])
			k++;
		if (substr[k] == 0)
			return (1);
		i++;
	}
	return (0);
}
