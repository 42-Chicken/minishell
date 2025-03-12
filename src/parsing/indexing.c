/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   indexing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efranco <efranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:22:35 by rguigneb          #+#    #+#             */
/*   Updated: 2025/03/12 15:14:23 by efranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "limits.h"
#include "parsing.h"

typedef struct s_init_index
{
	int		min;
	t_token	*tmp;
	int		i;
	int		size;
	t_token	*head_tokens;
	t_token	*head_args;
	t_token	*head_quoted;
}			t_init_index;

void	update_min_token(t_token **tokens, t_token **tmp, int *min)
{
	while (*tokens)
	{
		if ((*tokens)->index < *min && (*tokens)->num < 0)
		{
			*tmp = *tokens;
			*min = (*tokens)->index;
		}
		*tokens = (*tokens)->next;
	}
}

void	init_data(t_init_index *data, t_token *tokens, t_token *args,
		t_token *quoted)
{
	data->tmp = NULL;
	data->i = 0;
	data->size = ft_tokensize(tokens) + ft_tokensize(args)
		+ ft_tokensize(quoted);
	data->head_tokens = tokens;
	data->head_args = args;
	data->head_quoted = quoted;
}

void	init_all_index(t_token *tokens, t_token *args, t_token *quoted)
{
	t_init_index	data;

	init_data(&data, tokens, args, quoted);
	while (data.i < data.size)
	{
		data.min = INT_MAX;
		tokens = data.head_tokens;
		update_min_token(&tokens, &data.tmp, &data.min);
		args = data.head_args;
		update_min_token(&args, &data.tmp, &data.min);
		quoted = data.head_quoted;
		update_min_token(&quoted, &data.tmp, &data.min);
		data.tmp->num = data.i;
		data.i++;
	}
}

t_token	*get_index_lst(int index, t_token *keywords, t_token *args,
		t_token *quoted)
{
	while (keywords)
	{
		if (index == keywords->num)
			return (keywords);
		keywords = keywords->next;
	}
	while (args)
	{
		if (index == args->num)
			return (args);
		args = args->next;
	}
	while (quoted)
	{
		if (index == quoted->num)
			return (quoted);
		quoted = quoted->next;
	}
	return (NULL);
}
