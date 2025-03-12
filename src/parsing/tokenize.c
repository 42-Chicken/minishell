/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:20:57 by rguigneb          #+#    #+#             */
/*   Updated: 2025/03/12 14:45:13 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	handle_pipe(t_token **tokens, t_minishell *data, char *input, int *i)
{
	if (input[*i] == '|' && is_in_quote_at(input, *i) == QUOTE_NONE)
	{
		if (input[*i + 1] == '|')
		{
			*i += 2;
			if (input[*i] == '|')
			{
				printf("Erreur de syntaxe : TRIPLE PIPE\n");
				data->exit_code = 2;
				return (1);
			}
			add_token(tokens, TOKEN_OR, "||", -1, *i - 2, get_priority_at(input,
					*i - 2));
		}
		else
		{
			add_token(tokens, TOKEN_PIPE, "|", -1, *i - 1,
				get_priority_at(input, *i));
			(*i)++;
		}
	}
	return (0);
}

int	handle_redirection(t_token **tokens, char *input, int *i)
{
	if (input[*i] == '<' && is_in_quote_at(input, *i) == QUOTE_NONE)
	{
		if (input[*i + 1] == '<')
		{
			*i += 2;
			if (input[*i] == '<')
			{
				printf("Erreur de syntaxe : TRIPLE HEREDOC\n");
				return (1);
			}
			add_token(tokens, TOKEN_HEREDOC, "<<", -1, *i - 2,
				get_priority_at(input, *i - 2));
		}
		else
		{
			add_token(tokens, TOKEN_REDIR_IN, "<", -1, *i - 1,
				get_priority_at(input, *i));
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
	while (ft_isspace(input[i]))
		i++;
	while (input[i])
	{
		if (handle_pipe(&tokens, data, input, &i))
			return (NULL);
		if (handle_redirection(&tokens, input, &i))
			return (NULL);
		if (handle_append(&tokens, input, &i))
			return (NULL);
		if (handle_and(&tokens, input, &i))
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
