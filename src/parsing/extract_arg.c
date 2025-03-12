/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_arg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:19:11 by rguigneb          #+#    #+#             */
/*   Updated: 2025/03/12 14:46:54 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	skip_to_end_of_quoted_section(char *line, int *i)
{
	while (line[*i] && ((!ft_isspace(line[*i]) && !is_keyword(line[*i], 0))
			|| (is_keyword(line[*i], 0) && is_in_quote_at(line,
					*i) != QUOTE_NONE) || (ft_isspace(line[*i])
				&& is_in_quote_at(line, *i) != QUOTE_NONE)))
	{
		(*i)++;
	}
}

void	adjust_start_position(char *line, int *i)
{
	while (*i - 1 >= 0 && ((!ft_isspace(line[*i - 1]) && !is_keyword(line[*i
					- 1], 0)) || (is_keyword(line[*i], 0)
				&& is_in_quote_at(line, *i) != QUOTE_NONE)))
	{
		(*i)--;
	}
}

void	process_keyword(char *line, int *i, int *h, t_token **args)
{
	if (*i != *h)
		add_token(args, TOKEN_WORD, line + *h, *i - *h, *h,
			get_priority_at(line, *h + 1));
	if (is_keyword(line[*i + 1], 0) == 1)
		(*i)++;
	*h = *i + 1;
}

void	process_quoted_section(char *line, int *i, int *h, t_token **args,
		t_token **head)
{
	char	flag;
	int		count;

	flag = line[*i];
	count = 0;
	adjust_start_position(line, i);
	if (*i != *h)
		add_token(args, TOKEN_WORD, line + *h, *i - *h, *h,
			get_priority_at(line, *h));
	*h = *i;
	while (line[*i] && count < 2)
	{
		if (line[*i] == flag)
			count++;
		if (count == 2)
			skip_to_end_of_quoted_section(line, i);
		else
			(*i)++;
	}
	add_token(head, TOKEN_QUOTED, line + *h, *i - *h, *h, get_priority_at(line,
			*h + 1));
	*h = *i;
}

t_token	*extract_arg(char *line, t_token **head)
{
	t_token	*args;
	int		i;
	int		h;

	i = 0;
	args = NULL;
	h = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '"')
		{
			process_quoted_section(line, &i, &h, &args, head);
			continue ;
		}
		if (is_keyword(line[i], 0) == 1)
		{
			process_keyword(line, &i, &h, &args);
		}
		i++;
	}
	if (line[h])
		add_token(&args, TOKEN_WORD, line + h, i - h, h, get_priority_at(line, h
				+ 1));
	return (args);
}
