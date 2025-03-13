/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:20:57 by rguigneb          #+#    #+#             */
/*   Updated: 2025/03/13 16:03:53 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <define.h>

int	do_error(t_minishell *data, const char *error)
{
	printf("%s", error);
	data->execution_tree_error = EXECTREE_ERR_CANCEL;
	data->exit_code = 2;
	return (1);
}

int	handle_pipe(t_minishell *data, t_token **tokens, char *input, int *i)
{
	if (input[*i] == '|' && is_in_quote_at(input, *i) == QUOTE_NONE)
	{
		if (input[*i + 1] == '|')
		{
			*i += 2;
			if (input[*i] == '|')
			{
				do_error(data, ERROR_TREE_PIPE);
				return (1);
			}
			add_token(tokens, TOKEN_OR, (t_token_data){"||", -1, *i - 2,
				get_priority_at(input, *i - 2)});
		}
		else
		{
			add_token(tokens, TOKEN_PIPE, (t_token_data){"|", -1, *i - 1,
				get_priority_at(input, *i)});
			(*i)++;
		}
	}
	return (0);
}

int	handle_redirection(t_minishell *data, t_token **tokens, char *input, int *i)
{
	if (input[*i] == '<' && is_in_quote_at(input, *i) == QUOTE_NONE)
	{
		if (input[*i + 1] == '<')
		{
			*i += 2;
			if (input[*i] == '<')
			{
				do_error(data, ERROR_CLOSSING_REDIR);
				return (1);
			}
			else if (is_keyword(input[*i], 0) != 0)
				return (do_error(data, ERROR_TREE_PIPE), 1);
			add_token(tokens, TOKEN_HEREDOC, (t_token_data){"<<", -1, *i - 2,
				get_priority_at(input, *i - 2)});
		}
		else if (is_keyword(input[*i + 1], 0) != 0)
			return (do_error(data, ERROR_UNEXPTED_TOKEN_NEW_LINE), 1);
		else
		{
			add_token(tokens, TOKEN_REDIR_IN, (t_token_data){"<", -1, *i - 1,
				get_priority_at(input, *i)});
			(*i)++;
		}
	}
	return (0);
}

void	handle_quotes(char *input, int *i)
{
	char	flag;

	flag = input[*i];
	(*i)++;
	while (input[*i] != flag)
		(*i)++;
	(*i)++;
}

t_token	*tokenize(t_minishell *data, char *input)
{
	t_token	*tokens;
	int		i;

	tokens = NULL;
	i = 0;
	while (input[i] && ft_isspace(input[i]))
		i++;
	while (i < (int)ft_strlen(input) && input[i])
	{
		if (handle_pipe(data, &tokens, input, &i))
			return (NULL);
		if (handle_redirection(data, &tokens, input, &i))
			return (NULL);
		if (handle_append(data, &tokens, input, &i))
			return (NULL);
		if (handle_and(data, &tokens, input, &i))
			return (NULL);
		if (input[i] == '"' || input[i] == '\'')
		{
			handle_quotes(input, &i);
			continue ;
		}
		i++;
	}
	return (tokens);
}
