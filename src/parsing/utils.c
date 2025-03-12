/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:26:57 by rguigneb          #+#    #+#             */
/*   Updated: 2025/03/12 14:41:16 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	get_max_lst(t_token *keywords, t_token *args, t_token *quoted)
{
	int	max;

	max = INT_MIN;
	while (keywords)
	{
		if (max < keywords->num)
			max = keywords->num;
		keywords = keywords->next;
	}
	while (args)
	{
		if (max < args->num)
			max = args->num;
		args = args->next;
	}
	while (quoted)
	{
		if (max < quoted->num)
			max = quoted->num;
		quoted = quoted->next;
	}
	return (max);
}

int	line_is_empty(t_token *current)
{
	int	i;

	i = 0;
	if (!current || !current->value)
		return (1);
	if (current->type == TOKEN_WORD || current->type == TOKEN_QUOTED)
	{
		while (current->value[i])
		{
			if (current->value[i] != ' ')
			{
				return (0);
			}
			i++;
		}
		return (1);
	}
	return (0);
}

bool	only_spaces(char *str, unsigned int index)
{
	unsigned int	i;

	i = 0;
	while (str && str[++i] && i < index)
	{
		if (!ft_isspace(str[i]))
			return (false);
	}
	return (true);
}
