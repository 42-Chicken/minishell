/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efranco <efranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 14:28:58 by rguigneb          #+#    #+#             */
/*   Updated: 2025/02/27 14:49:46 by efranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

t_token	*ft_tokenlast(t_token *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	ft_tokenadd_back(t_token **lst, t_token *new)
{
	t_token	*last;

	if (!lst || !new)
		return ;
	last = *lst;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = ft_tokenlast((*lst));
	last->next = new;
}

t_token	*add_token(t_token **head, TokenType type, char *value, int i)
{
	t_token	*new;

	new = safe_malloc(sizeof(t_token));
	ft_bzero(new, sizeof(new));
	new->type = type;
	if (i == -1)
		new->value = ft_strdup(value);
	else
		new->value = ft_strndup(value, i);
	new->next = NULL;
	ft_tokenadd_back(head, new);
	return (new);
}

int	without_quote(char *str)
{
	int		size;
	int		i;
	char	flag;

	size = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			flag = str[i];
			i++;
			while (str[i] && str[i] != flag)
				i++;
			if (str[i] == flag)
				i++;
		}
		else
		{
			i++;
			size++;
		}
	}
	return (size);
}
char	*extract_quoted(char *str, t_token **head)
{
	char	*new_line;
	char	flag;
	int		i;
	int		j;
	int		h;

	new_line = safe_malloc(sizeof(char) * without_quote(str) + 1);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			flag = str[i];
			i++;
			h = i;
			while (str[i] && str[i] != flag)
				i++;
			if (str[i] == flag)
			{
				add_token(head, TOKEN_WORD, str + h, i - h);
				i++;
			}
			else
				return (NULL);
		}
		else
		{
			new_line[j] = str[i];
			i++;
			j++;
		}
	}
	new_line[j] = '\0';
	return(new_line);
}

int	is_keyword(char c)
{
	if (c == '|')
		return (1);
	if (c == '&')
		return (1);
	if (c == '<')
		return (1);
	if (c == '>')
		return (1);
	else
		return (0);
}

t_token	*extract_arg(char *line)
{
	t_token	*args;
	int		i;
	int		h;

	i = 0;
	h = 0;
	args = NULL;
	while (line[i])
	{
		if (is_keyword(line[i]) == 1)
		{
			add_token(&args, TOKEN_WORD, line + h, i - h);
			if (is_keyword(line[i + 1]) == 1)
				i++;
			h = i + 1;
		}
		i++;
	}
	if (h < i)
		add_token(&args, TOKEN_WORD, line + h, i - h);
	return (args);
}
t_token	*tokenize(char *input)
{
	t_token	*tokens;
	t_token	*args;
	int		i;

	tokens = NULL;
	args = NULL;
	i = 0;
	while (ft_isspace(input[i]))
		i++;
	while (input[i])
	{
		if (input[i] == '|')
		{
			if (input[i + 1] == '|')
			{
				i++;
				if (input[i + 1] == '|')
				{
					printf("Erreur de syntaxe : TRIPLE PIPE\n");
					return (NULL);
				}
				add_token(&tokens, TOKEN_OR, "||", -1);
			}
			else
			{
				add_token(&tokens, TOKEN_PIPE, "|", -1);
				i++;
			}
		}
		else if (input[i] == '<')
		{
			if (input[i + 1] == '<')
			{
				i++;
				if (input[i + 1] == '<')
				{
					printf("Erreur de syntaxe : TRIPLE HEREDOC\n");
					return (NULL);
				}
				add_token(&tokens, TOKEN_HEREDOC, "<<", -1);
			}
			else
			{
				add_token(&tokens, TOKEN_REDIR_IN, "<", -1);
				i++;
			}
		}
		else if (input[i] == '>')
		{
			if (input[i + 1] == '>')
			{
				i++;
				if (input[i + 1] == '>')
				{
					printf("Erreur de syntaxe : TRIPLE APPEND\n");
					return (NULL);
				}
				add_token(&tokens, TOKEN_APPEND, ">>", -1);
			}
			else
			{
				add_token(&tokens, TOKEN_REDIR_OUT, ">", -1);
				i++;
			}
		}
		else if (input[i] == '&')
		{
			if (input[i + 1] == '&')
			{
				i++;
				if (input[i + 1] == '&')
				{
					printf("Erreur de syntaxe : TRIPLE AND\n");
					return (NULL);
				}
				add_token(&tokens, TOKEN_AND, "&&", -1);
			}
			else
			{
				printf("Erreur de syntaxe : UNIQUE &\n");
				return (NULL);
			}
		}
		else
			i++;
	}
	return (tokens);
}

void	parse_line(t_minishell *data, char *line)
{
	t_token	*tokens;
	t_token	*args;
	t_token	*quoted;
	char	*new_line;

	quoted = NULL;
	new_line = extract_quoted(line, &quoted);
	if (new_line == NULL)
	{
		ft_fprintf(STDERR_FILENO, "Erreur de quote\n");
		return ;
	}
	tokens = tokenize(new_line);
	args = extract_arg(new_line);
	while (quoted)
	{
		printf("Quoted : %s\n", quoted->value);
		quoted = quoted->next;
	}
	while (tokens)
	{
		printf("Type de Token : %d\n", tokens->type);
		tokens = tokens->next;
	}
	while (args)
	{
		printf("Differents arguments : %s\n", args->value);
		args = args->next;
	}
}
