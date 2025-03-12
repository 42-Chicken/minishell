/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proprieties.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:31:10 by rguigneb          #+#    #+#             */
/*   Updated: 2025/03/12 14:41:07 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

unsigned int	get_priority_at(char *str, unsigned int index)
{
	unsigned int	i;
	unsigned int	priority;

	i = -1;
	priority = 0;
	while (str[++i] && i <= index)
	{
		if (str[i] == '(' && is_in_quote_at(str, i) == QUOTE_NONE)
		{
			if (ft_strchr(str + i, ')') && is_in_quote_at(ft_strchr(str + i,
						')'), 0) == QUOTE_NONE)
				priority++;
		}
		else if (str[i] == ')' && is_in_quote_at(str, i) == QUOTE_NONE)
		{
			if (priority > 0)
				priority--;
		}
	}
	return (priority);
}

bool	check_priorities(char *str)
{
	unsigned int	i;
	unsigned int	priority;

	i = -1;
	priority = 0;
	while (str && str[++i])
	{
		if (str[i] == '(' && is_in_quote_at(str, i) == QUOTE_NONE)
		{
			if (ft_strchr(str + i, ')') && is_in_quote_at(ft_strchr(str + i,
						')'), 0) == QUOTE_NONE)
				priority++;
			else
				return (ft_fprintf(STDERR_FILENO,
						"minishell: brackets are not closed properly `)'\n"),
					true);
			if (only_spaces(str + i, ft_strchr(str + i, ')') - (str + i)))
				return (ft_fprintf(STDERR_FILENO,
						"minishell: syntax error near unexpected token `)'\n"),
					true);
		}
		else if (str[i] == ')' && is_in_quote_at(str, i) == QUOTE_NONE)
		{
			if (priority > 0)
				priority--;
			else
				return (ft_fprintf(STDERR_FILENO, "Error: too many `)'\n"),
					true);
		}
	}
	return (false);
}
