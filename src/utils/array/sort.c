/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 11:13:37 by rguigneb          #+#    #+#             */
/*   Updated: 2025/02/20 11:17:30 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	char_sort_array(char **tab)
{
	int		i;
	int		y;
	int		len;
	char	*temp;

	if (!tab)
		return ;
	i = -1;
	len = char_array_len(tab);
	while (++i < len && tab[i])
	{
		y = -1;
		while (++y < len && tab[y])
		{
			if (ft_strncmp(tab[i], tab[y], ft_strlen(tab[i])) < 0)
			{
				temp = tab[i];
				tab[i] = tab[y];
				tab[y] = temp;
			}
		}
	}
}
