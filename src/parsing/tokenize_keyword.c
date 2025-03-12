/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_keyword.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:42:57 by rguigneb          #+#    #+#             */
/*   Updated: 2025/03/12 14:43:01 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	handle_append(t_token **tokens, char *input, int *i)
{
	if (input[*i] == '>' && is_in_quote_at(input, *i) == QUOTE_NONE)
	{
		if (is_keyword(input[*i + 1], 4))
			(*i)++;
		if (input[*i + 1] == '>')
		{
			*i += 2;
			if (input[*i] == '>')
			{
				printf("Erreur de syntaxe : TRIPLE APPEND\n");
				return (1);
			}
			add_token(tokens, TOKEN_APPEND, ">>", -1, *i - 2,
				get_priority_at(input, *i - 2));
		}
		else
		{
			add_token(tokens, TOKEN_REDIR_OUT, ">", -1, *i - 1,
				get_priority_at(input, *i));
			(*i)++;
		}
	}
	return (0);
}

int	handle_and(t_token **tokens, char *input, int *i)
{
	if (input[*i] == '&' && is_in_quote_at(input, *i) == QUOTE_NONE)
	{
		if (input[*i + 1] == '&')
		{
			*i += 2;
			if (input[*i] == '&')
			{
				printf("Erreur de syntaxe : TRIPLE AND\n");
				return (1);
			}
			add_token(tokens, TOKEN_AND, "&&", -1, *i - 2,
				get_priority_at(input, *i - 2));
		}
		else
		{
			printf("Erreur de syntaxe : UNIQUE &\n");
			return (1);
		}
	}
	return (0);
}
