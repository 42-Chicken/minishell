/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_keyword.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:42:57 by rguigneb          #+#    #+#             */
/*   Updated: 2025/03/13 12:34:29 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <define.h>

int	handle_append(t_minishell *data, t_token **tokens, char *input, int *i)
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
				printf(ERROR_OPENING_REDIR);
				data->execution_tree_error = EXECTREE_ERR_CANCEL;
				data->exit_code = 2;
				return (1);
			}
			add_token(tokens, TOKEN_APPEND, (t_token_data){">>", -1, *i - 2,
				get_priority_at(input, *i - 2)});
		}
		else
		{
			add_token(tokens, TOKEN_REDIR_OUT, (t_token_data){">", -1, *i - 1,
				get_priority_at(input, *i)});
			(*i)++;
		}
	}
	return (0);
}

int	handle_and(t_minishell *data, t_token **tokens, char *input, int *i)
{
	if (input[*i] == '&' && is_in_quote_at(input, *i) == QUOTE_NONE)
	{
		if (input[*i + 1] == '&')
		{
			*i += 2;
			if (input[*i] == '&')
			{
				printf(ERROR_SYNTAX_AND);
				data->execution_tree_error = EXECTREE_ERR_CANCEL;
				data->exit_code = 2;
				return (1);
			}
			add_token(tokens, TOKEN_AND, (t_token_data){"&&", -1, *i - 2,
				get_priority_at(input, *i - 2)});
		}
		else
		{
			printf(ERROR_SYNTAX_UNIQUE_AND);
			data->execution_tree_error = EXECTREE_ERR_CANCEL;
			data->exit_code = 2;
			return (1);
		}
	}
	return (0);
}
