/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:28:15 by rguigneb          #+#    #+#             */
/*   Updated: 2025/03/13 08:39:38 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*allocate_clean_string(char *value)
{
	int		size;
	char	*str;

	size = ft_strlen(value) - ft_number_quote(value);
	str = safe_malloc(sizeof(char) * (size + 1));
	return (str);
}

void	process_quotes(char *value, char *str, int *i, int *j)
{
	char	flag;

	flag = value[*i];
	(*i)++;
	while (value[*i] && value[*i] != flag)
	{
		str[*j] = value[*i];
		(*j)++;
		(*i)++;
	}
	if (value[*i])
		(*i)++;
}

char	*remove_quotes_from_value(char *value)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	str = allocate_clean_string(value);
	while (value[i])
	{
		if (value[i] == '"' || value[i] == '\'')
			process_quotes(value, str, &i, &j);
		else
		{
			str[j] = value[i];
			j++;
			i++;
		}
	}
	str[j] = '\0';
	return (str);
}

void	extract_quote(t_token **head, t_token *quoted)
{
	char	*str;

	while (quoted)
	{
		if (check_only_quote(quoted->value) == 1)
		{
			quoted = quoted->next;
			continue ;
		}
		str = remove_quotes_from_value(quoted->value);
		add_token(head, TOKEN_QUOTED, (t_token_data){str, -1, quoted->index,
			get_priority_at(str, quoted->index)});
		quoted = quoted->next;
	}
}
