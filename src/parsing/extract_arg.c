/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_arg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:19:11 by rguigneb          #+#    #+#             */
/*   Updated: 2025/03/13 08:35:48 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

typedef struct s_extract
{
	t_token	*args;
	int		i;
	int		h;
}			t_extract;

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

void	process_quoted_section(char *line, t_extract *data, t_token **head)
{
	char	flag;
	int		count;

	flag = line[data->i];
	count = 0;
	adjust_start_position(line, &data->i);
	if (data->i != data->h)
		add_token(&data->args, TOKEN_WORD, line + data->h, data->i - data->h,
			data->h, get_priority_at(line, data->h));
	data->h = data->i;
	while (line[data->i] && count < 2)
	{
		if (line[data->i] == flag)
			count++;
		if (count == 2)
			skip_to_end_of_quoted_section(line, &data->i);
		else
			(data->i)++;
	}
	add_token(head, TOKEN_QUOTED, line + data->h, data->i - data->h, data->h,
		get_priority_at(line, data->h + 1));
	data->h = data->i;
}

t_token	*extract_arg(char *line, t_token **head)
{
	t_extract	data;

	data = (t_extract){0, 0, 0};
	while (line[data.i])
	{
		if (line[data.i] == '\'' || line[data.i] == '"')
		{
			process_quoted_section(line, &data, head);
			continue ;
		}
		if (is_keyword(line[data.i], 0) == 1)
		{
			process_keyword(line, &data.i, &data.h, &data.args);
		}
		data.i++;
	}
	if (line[data.h])
		add_token(&data.args, TOKEN_WORD, line + data.h, data.i - data.h,
			data.h, get_priority_at(line, data.h + 1));
	return (data.args);
}
