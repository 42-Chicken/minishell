/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   indexing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:22:35 by rguigneb          #+#    #+#             */
/*   Updated: 2025/03/12 14:48:29 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "limits.h"
#include "parsing.h"

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

void	init_all_index(t_token *tokens, t_token *args, t_token *quoted)
{
	int		min;
	t_token	*tmp;
	int		i;
	int		size;
	t_token	*head_tokens;
	t_token	*head_args;
	t_token	*head_quoted;

	tmp = NULL;
	i = 0;
	size = ft_tokensize(tokens) + ft_tokensize(args) + ft_tokensize(quoted);
	head_tokens = tokens;
	head_args = args;
	head_quoted = quoted;
	while (i < size)
	{
		min = INT_MAX;
		tokens = head_tokens;
		update_min_token(&tokens, &tmp, &min);
		args = head_args;
		update_min_token(&args, &tmp, &min);
		quoted = head_quoted;
		update_min_token(&quoted, &tmp, &min);
		tmp->num = i;
		i++;
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
