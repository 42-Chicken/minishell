/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_custom_strreplace.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:08:05 by rguigneb          #+#    #+#             */
/*   Updated: 2025/03/12 15:13:25 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_replacment(char **result, char *str, char *mask, size_t *i)
{
	if (get_next_cmp_index(str, mask, *i) == 0)
	{
		*result = ft_strnjoin(*result, str + *i, 1);
		*i += 1;
	}
	else
	{
		*result = ft_strnjoin(*result, str + *i, get_next_cmp_index(str, mask,
					*i));
		*i += get_next_cmp_index(str, mask, *i);
	}
}

char	*ft_custom_strreplace(char *str, char *mask, char *value)
{
	char	*result;
	size_t	i;

	i = 0;
	result = ft_strdup("");
	if (!str)
		return (NULL);
	if (!mask || !mask[0] || !value)
		return (ft_strdup(str));
	while (str[i])
	{
		if (ft_strncmp(str + i, mask, ft_strlen(mask)) == 0
			&& is_in_quote_at(str, i) != QUOTE_SIMPLE)
		{
			result = ft_strjoin(result, value);
			i += ft_strlen(mask);
		}
		else
			handle_replacment(&result, str, mask, &i);
	}
	return (result);
}
