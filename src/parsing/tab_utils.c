/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:29:44 by rguigneb          #+#    #+#             */
/*   Updated: 2025/03/12 14:41:09 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	tab_len(char **str)
{
	int	i;

	i = 0;
	if (!str || !*str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	**add_tab_to_tab(char **old, char **str)
{
	char	**tab;
	int		size;
	int		i;
	int		j;

	size = tab_len(old) + tab_len(str);
	i = 0;
	tab = safe_malloc(sizeof(char *) * (size + 1));
	ft_bzero(tab, sizeof(char *) * (size + 1));
	while (old && old[i])
	{
		tab[i] = old[i];
		i++;
	}
	j = 0;
	while (str && str[j])
		tab[i++] = str[j++];
	tab[i] = NULL;
	return (tab);
}

char	**add_to_tab(char **old, char *str)
{
	char	**tab;
	int		size;
	int		i;

	size = tab_len(old);
	i = 0;
	tab = safe_malloc(sizeof(char *) * (size + 2));
	ft_bzero(tab, sizeof(char *) * (size + 2));
	while (old && old[i])
	{
		tab[i] = old[i];
		i++;
	}
	tab[i++] = str;
	tab[i] = NULL;
	return (tab);
}
