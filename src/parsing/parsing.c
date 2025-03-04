/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efranco <efranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 14:28:58 by rguigneb          #+#    #+#             */
/*   Updated: 2025/03/04 14:58:46 by efranco          ###   ########.fr       */
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

t_token	*add_token(t_token **head, TokenType type, char *value, int i, int h)
{
	t_token	*new;

	new = safe_malloc(sizeof(t_token));
	ft_bzero(new, sizeof(new));
	new->type = type;
	if (i == -1)
		new->value = ft_strdup(value);
	else
		new->value = ft_strndup(value, i);
	// if (type == TOKEN_WORD)
	// 	new->value = ft_strtrim(new->value, SPACES);
	new->next = NULL;
	new->index = h;
	new->num = -1;
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
// char	*extract_quoted(char *str, t_token **head)
// {
// 	char	*new_line;
// 	char	flag;
// 	int		i;
// 	int		j;
// 	int		h;

// 	new_line = safe_malloc(sizeof(char) * without_quote(str) + 1);
// 	i = 0;
// 	j = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == '\'' || str[i] == '"')
// 		{
// 			flag = str[i];
// 			i++;
// 			h = i;
// 			while (str[i] && str[i] != flag)
// 				i++;
// 			if (str[i] == flag)
// 			{
// 				add_token(head, TOKEN_WORD, str + h, i - h, h);
// 				i++;
// 			}
// 			else
// 				return (NULL);
// 		}
// 		else
// 		{
// 			new_line[j] = str[i];
// 			i++;
// 			j++;
// 		}
// 	}
// 	new_line[j] = '\0';
// 	return (new_line);
// }

int	is_keyword(char c, int flag)
{
	if (c == '|' && flag != 1)
		return (1);
	if (c == '&' && flag != 2)
		return (1);
	if (c == '<' && flag != 3)
		return (1);
	if (c == '>' && flag != 4)
		return (1);
	else
		return (0);
}

t_token	*extract_arg(char *line, t_token **head)
{
	t_token	*args;
	int		i;
	int		h;
	char	flag;

	i = 0;
	h = 0;
	args = NULL;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '"')
		{
			add_token(&args, TOKEN_WORD, line + h, i - h, h);
			flag = line[i];
			i++;
			h = i;
			while (line[i] && line[i] != flag)
				i++;
			if (line[i] == flag)
			{
				add_token(head, TOKEN_QUOTED, line + h, i - h, h);
				i++;
				h = i;
			}
			else
				return (NULL);
		}
		if (is_keyword(line[i], 0) == 1)
		{
			add_token(&args, TOKEN_WORD, line + h, i - h, h);
			if (is_keyword(line[i + 1], 0) == 1)
				i++;
			h = i + 1;
		}
		i++;
	}
	if (line[h])
		add_token(&args, TOKEN_WORD, line + h, i - h, h);
	return (args);
}
t_token	*tokenize(char *input)
{
	t_token	*tokens;
	t_token	*args;
	int		i;
	char	flag;

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
				i += 2;
				if (input[i] == '|')
				{
					printf("Erreur de syntaxe : TRIPLE PIPE\n");
					return (NULL);
				}
				add_token(&tokens, TOKEN_OR, "||", -1, i - 2);
			}
			else
			{
				add_token(&tokens, TOKEN_PIPE, "|", -1, i - 1);
				i++;
			}
		}
		else if (input[i] == '<')
		{
			if (input[i + 1] == '<')
			{
				i += 2;
				if (input[i] == '<')
				{
					printf("Erreur de syntaxe : TRIPLE HEREDOC\n");
					return (NULL);
				}
				add_token(&tokens, TOKEN_HEREDOC, "<<", -1, i - 2);
			}
			else
			{
				add_token(&tokens, TOKEN_REDIR_IN, "<", -1, i - 1);
				i++;
			}
		}
		else if (input[i] == '>')
		{
			if (is_keyword(input[i + 1], 4))
				i++;
			if (input[i + 1] == '>')
			{
				i += 2;
				if (input[i] == '>')
				{
					printf("Erreur de syntaxe : TRIPLE APPEND\n");
					return (NULL);
				}
				add_token(&tokens, TOKEN_APPEND, ">>", -1, i - 2);
			}
			else
			{
				add_token(&tokens, TOKEN_REDIR_OUT, ">", -1, i - 1);
				i++;
			}
		}
		else if (input[i] == '&')
		{
			if (input[i + 1] == '&')
			{
				i += 2;
				if (input[i] == '&')
				{
					printf("Erreur de syntaxe : TRIPLE AND\n");
					return (NULL);
				}
				add_token(&tokens, TOKEN_AND, "&&", -1, i - 2);
			}
			else
			{
				printf("Erreur de syntaxe : UNIQUE &\n");
				return (NULL);
			}
		}
		else if (input[i] == '"' || input[i] == '\'')
		{
			flag = input[i];
			i++;
			while (input[i] != flag)
				i++;
			i++;
		}
		else
			i++;
	}
	return (tokens);
}
void init_all_index(t_token *tokens, t_token *args, t_token *quoted)
{
	int 	min;
	t_token *tmp;
	int		i;
	int		size;
	t_token	*head_tokens;
	t_token	*head_args;
	t_token	*head_quoted;

	i = 0;
	tmp = NULL;
	size = ft_tokensize(tokens) + ft_tokensize(args) + ft_tokensize(quoted);
	head_tokens = tokens;
	head_args = args;
	head_quoted = quoted;

	while(i < size)
	{
		min = INT_MAX;
		tokens = head_tokens;
		while(tokens)
		{
			if(tokens->index < min && tokens->num < 0)
			{
				tmp = tokens;
				min = tokens->index;
			}
			tokens = tokens->next;
		}
		args = head_args;
		while(args)
		{
			if(args->index < min && args->num < 0)
			{
				tmp = args;
				min = args->index;
			}
			args = args->next;
		}
		quoted = head_quoted;
		while(quoted)
		{
			if(quoted->index < min && quoted->num < 0)
			{
				tmp = quoted;
				min = quoted->index;
			}
			quoted = quoted->next;
		}
		tmp->num = i;
		i++;
	}
}
void convert_to_btree(t_token *keywords, t_token *args, t_token *quoted)
{

}

void	parse_line(t_minishell *data, char *line)
{
	t_token	*keywords;
	t_token	*args;
	t_token	*quoted;

	quoted = NULL;
	keywords = tokenize(line);
	args = extract_arg(line, &quoted);
	if (args == NULL)
	{
		ft_fprintf(STDERR_FILENO, "Erreur de quote\n");
		return ;
	}
	init_all_index(keywords, args, quoted);
	while (quoted)
	{
		printf("Quoted : [%s] | Index : [%d]\n", quoted->value, quoted->num);
		quoted = quoted->next;
	}
	while (keywords)
	{
		printf("Token : [%s] | Index : [%d]\n", keywords->value, keywords->num);
		keywords = keywords->next;
	}
	while (args)
	{
		printf("arguments : [%s] | Index : [%d]\n", args->value, args->num);
		args = args->next;
	}
}
