/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 14:48:28 by rguigneb          #+#    #+#             */
/*   Updated: 2025/01/27 08:56:47 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "garbadge.h"

void	free_split_until_end(char **tab, int from)
{
	while (tab[from])
		free(tab[from++]);
	free(tab);
}

void	free_split(char **tab, int index)
{
	while (index)
		free(tab[index--]);
	free(tab);
}

size_t	get_next_set_occurency(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

size_t	get_word_count(char const *s, char c)
{
	size_t	i;
	size_t	is_in_word;
	size_t	count;

	i = -1;
	is_in_word = 0;
	count = 0;
	while (s[++i])
	{
		if (s[i] == c)
			is_in_word = 0;
		else if (is_in_word++ == 0)
			count++;
	}
	return (count);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	total_len;
	size_t	next_char_index;
	char	**tab;

	i = 0;
	total_len = get_word_count(s, c) * sizeof(char *) + sizeof(NULL);
	tab = (char **)MALLOC(total_len);
	if (!tab)
		return (NULL);
	while (*s)
	{
		if (*s == c)
			s++;
		else
		{
			next_char_index = get_next_set_occurency(s, c);
			tab[i++] = ft_substr(s, 0, next_char_index);
			if (!tab[i - 1])
				free_split(tab, i - 1);
			s += next_char_index;
		}
	}
	tab[i] = NULL;
	return (tab);
}
