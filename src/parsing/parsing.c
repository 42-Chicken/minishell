/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 14:28:58 by rguigneb          #+#    #+#             */
/*   Updated: 2025/03/12 13:15:45 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "define.h"
#include "minishell.h"
#include "parsing.h"
#include <limits.h>

int	get_max_lst(t_token *keywords, t_token *args, t_token *quoted)
{
	int	max;

	max = INT_MIN;
	while (keywords)
	{
		if (max < keywords->num)
			max = keywords->num;
		keywords = keywords->next;
	}
	while (args)
	{
		if (max < args->num)
			max = args->num;
		args = args->next;
	}
	while (quoted)
	{
		if (max < quoted->num)
			max = quoted->num;
		quoted = quoted->next;
	}
	return (max);
}

int	line_is_empty(t_token *current)
{
	int	i;

	i = 0;
	if (!current || !current->value)
		return (1);
	if (current->type == TOKEN_WORD || current->type == TOKEN_QUOTED)
	{
		while (current->value[i])
		{
			if (current->value[i] != ' ')
			{
				return (0);
			}
			i++;
		}
		return (1);
	}
	return (0);
}

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

int	is_keywords(t_token *current)
{
	if (!current)
		return (0);
	if (current->type == TOKEN_AND || current->type == TOKEN_OR
		|| current->type == TOKEN_APPEND || current->type == TOKEN_HEREDOC
		|| current->type == TOKEN_PIPE || current->type == TOKEN_REDIR_IN
		|| current->type == TOKEN_REDIR_OUT)
		return (1);
	else
		return (0);
}

t_token	*add_token(t_token **head, t_e_token_type type, char *value, int i, int h,
		unsigned int priority)
{
	t_token	*new;

	new = safe_malloc(sizeof(t_token));
	ft_bzero(new, sizeof(t_token));
	new->type = type;
	if (i == -1)
		new->value = ft_strdup(value);
	else
		new->value = ft_strndup(value, i);
	if (new->value && ft_strlen(new->value) > 0 && type == TOKEN_WORD)
		new->value = ft_strtrim(new->value, SPACES "()");
	new->next = NULL;
	new->index = h;
	new->num = -1;
	new->priority = priority;
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
	if (c == '(' && flag != 4)
		return (1);
	if (c == ')' && flag != 4)
		return (1);
	else
		return (0);
}

int	verif_quote(char *line)
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
			flag = line[i];
			i++;
			while (line[i] && line[i] != flag)
				i++;
			if (line[i] == flag)
				i++;
			else
				return (flag);
		}
		else
			i++;
	}
	return (-1);
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

t_token	*extract_arg(char *line, t_token **head)
{
	t_token	*args;
	int		i;
	int		h;
	char	flag;
	int		count;

	i = 0;
	h = 0;
	args = NULL;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '"')
		{
			flag = line[i];
			while (i - 1 >= 0 && ((!ft_isspace(line[i - 1])
						&& !is_keyword(line[i - 1], 0)) || (is_keyword(line[i],
							0) && is_in_quote_at(line, i) != QUOTE_NONE)))
			{
				i--;
			}
			if (i != h)
				add_token(&args, TOKEN_WORD, line + h, i - h, h,
					get_priority_at(line, h));
			h = i;
			count = 0;
			while (line[i] && count < 2)
			{
				if (line[i] == flag)
					count++;
				if (count == 2)
				{
					while (line[i] && ((!ft_isspace(line[i])
								&& !is_keyword(line[i], 0))
							|| ((is_keyword(line[i], 0)) && is_in_quote_at(line,
									i) != QUOTE_NONE) || (ft_isspace(line[i])
								&& is_in_quote_at(line, i) != QUOTE_NONE)))
					{
						i++;
					}
				}
				else
					i++;
			}
			add_token(head, TOKEN_QUOTED, line + h, i - h, h,
				get_priority_at(line, h + 1));
			h = i;
			continue ;
		}
		if (is_keyword(line[i], 0) == 1)
		{
			if (i != h)
				add_token(&args, TOKEN_WORD, line + h, i - h, h,
					get_priority_at(line, h + 1));
			if (is_keyword(line[i + 1], 0) == 1)
				i++;
			h = i + 1;
		}
		i++;
	}
	if (line[h])
		add_token(&args, TOKEN_WORD, line + h, i - h, h, get_priority_at(line, h
				+ 1));
	return (args);
}

// char	*extract_from_line(char *str, int *i)
// {
// 	while (str && str[*i] && is_keyword(str[*i], 5))
// 		(*i)++;
// 	if (!str[i])
// 		return (NULL);
// 	while (str && str[*i] && !is_keyword(str[*i], 5) && !ft_isspace(str[*i]))
// 	{
// 		if ((str[*i] == '\'' || str[*i] == '"'))
// 		{
// 			if (ft_strchr(str, (str[*i])))
// 			{
// 				*i = ft_strchr(str, (str[*i])) - str;
// 				continue ;
// 			}
// 			else
// 				ft_fprintf(STDERR_FILENO, "ERROR QUOTES");
// 		}
// 		else
// 			(*i)++;
// 	}
// 	return (ft_substr(str, 0, *i));
// }

// t_token	*extract_arg(char *line, t_token **quoted)
// {
// 	t_token	*args;
// 	int		i;

// 	args = NULL;
// 	(void)quoted;
// 	i = 0;
// 	while (line[i])
// 	{
// 		printf("%s %d\n", extract_from_line(line + i, &i), i);
// 	}
// 	return (args);
// }

int	tab_len(char **str)
{
	int	i;

	i = 0;
	if (!str || !*str)
		return (0);
	while (str[i])
		i++;
	return (i);
}
char	**add_tab_to_tab(char **old, char **str)
{
	char	**tab;
	int		size;
	int		i;
	int		j;

	size = tab_len(old) + tab_len(str);
	i = 0;
	tab = safe_malloc(sizeof(char *) * (size + 1));
	ft_bzero(tab, sizeof(char *) * (size + 1));
	while (old && old[i])
	{
		tab[i] = old[i];
		i++;
	}
	j = 0;
	while (str && str[j])
		tab[i++] = str[j++];
	tab[i] = NULL;
	return (tab);
}
char	**add_to_tab(char **old, char *str)
{
	char	**tab;
	int		size;
	int		i;

	size = tab_len(old);
	i = 0;
	tab = safe_malloc(sizeof(char *) * (size + 2));
	ft_bzero(tab, sizeof(char *) * (size + 2));
	while (old && old[i])
	{
		tab[i] = old[i];
		i++;
	}
	tab[i++] = str;
	tab[i] = NULL;
	return (tab);
}

void	create_lst_args(t_list **head, t_token *keywords, t_token *args,
		t_token *quoted)
{
	t_list	*lst;
	char	**tab;
	int		index;
	int		max;
	int		priority;
	t_token	*current;
	t_token	*new_token;

	index = 0;
	tab = NULL;
	priority = 0;
	max = get_max_lst(keywords, args, quoted);
	lst = NULL;
	while (index <= max)
	{
		current = get_index_lst(index, keywords, args, quoted);
		while (current && (current->type == TOKEN_WORD
				|| current->type == TOKEN_QUOTED))
		{
			priority = current->priority;
			if (current && current->type == TOKEN_QUOTED)
			{
				tab = add_to_tab(tab, current->value);
			}
			else if (current && current->type == TOKEN_WORD
				&& line_is_empty(current) == 0)
			{
				tab = add_tab_to_tab(tab, ft_split(current->value, SPACES));
			}
			index++;
			current = get_index_lst(index, keywords, args, quoted);
		}
		if (current && is_keywords(current))
		{
			new_token = safe_malloc(sizeof(t_token));
			ft_bzero(new_token, sizeof(t_token));
			new_token->type = TOKEN_WORD;
			new_token->argv = tab;
			new_token->priority = priority;
			ft_lstadd_back(head, ft_lstnew(new_token));
			tab = NULL;
		}
		index++;
	}
	if (tab)
	{
		new_token = safe_malloc(sizeof(t_token));
		ft_bzero(new_token, sizeof(t_token));
		new_token->type = TOKEN_WORD;
		new_token->argv = tab;
		new_token->priority = priority;
		ft_lstadd_back(head, ft_lstnew(new_token));
	}
}

unsigned int	get_priority_at(char *str, unsigned int index)
{
	unsigned int	i;
	unsigned int	priority;

	i = -1;
	priority = 0;
	while (str[++i] && i <= index)
	{
		if (str[i] == '(' && is_in_quote_at(str, i) == QUOTE_NONE)
		{
			if (ft_strchr(str + i, ')') && is_in_quote_at(ft_strchr(str + i,
						')'), 0) == QUOTE_NONE)
				priority++;
		}
		else if (str[i] == ')' && is_in_quote_at(str, i) == QUOTE_NONE)
		{
			if (priority > 0)
				priority--;
		}
	}
	return (priority);
}

bool	only_spaces(char *str, unsigned int index)
{
	unsigned int	i;

	i = 0;
	while (str && str[++i] && i < index)
	{
		if (!ft_isspace(str[i]))
			return (false);
	}
	return (true);
}

bool	check_priorities(char *str)
{
	unsigned int	i;
	unsigned int	priority;

	i = -1;
	priority = 0;
	while (str && str[++i])
	{
		if (str[i] == '(' && is_in_quote_at(str, i) == QUOTE_NONE)
		{
			if (ft_strchr(str + i, ')') && is_in_quote_at(ft_strchr(str + i,
						')'), 0) == QUOTE_NONE)
				priority++;
			else
				return (ft_fprintf(STDERR_FILENO,
						"minishell: brackets are not closed properly `)'\n"),
					true);
			if (only_spaces(str + i, ft_strchr(str + i, ')') - (str + i)))
				return (ft_fprintf(STDERR_FILENO,
						"minishell: syntax error near unexpected token `)'\n"),
					true);
		}
		else if (str[i] == ')' && is_in_quote_at(str, i) == QUOTE_NONE)
		{
			if (priority > 0)
				priority--;
			else
				return (ft_fprintf(STDERR_FILENO, "Error: too many `)'\n"),
					true);
		}
	}
	return (false);
}

t_token	*tokenize(t_minishell *data, char *input)
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
		if (input[i] == '|' && is_in_quote_at(input, i) == QUOTE_NONE)
		{
			if (input[i + 1] == '|')
			{
				i += 2;
				if (input[i] == '|')
				{
					printf("Erreur de syntaxe : TRIPLE PIPE\n");
					data->exit_code = 2;
					return (NULL);
				}
				add_token(&tokens, TOKEN_OR, "||", -1, i - 2,
					get_priority_at(input, i - 2));
			}
			else
			{
				add_token(&tokens, TOKEN_PIPE, "|", -1, i - 1,
					get_priority_at(input, i));
				i++;
			}
		}
		else if (input[i] == '<' && is_in_quote_at(input, i) == QUOTE_NONE)
		{
			if (input[i + 1] == '<')
			{
				i += 2;
				if (input[i] == '<')
				{
					printf("Erreur de syntaxe : TRIPLE HEREDOC\n");
					return (NULL);
				}
				add_token(&tokens, TOKEN_HEREDOC, "<<", -1, i - 2,
					get_priority_at(input, i - 2));
			}
			else
			{
				add_token(&tokens, TOKEN_REDIR_IN, "<", -1, i - 1,
					get_priority_at(input, i));
				i++;
			}
		}
		else if (input[i] == '>' && is_in_quote_at(input, i) == QUOTE_NONE)
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
				add_token(&tokens, TOKEN_APPEND, ">>", -1, i - 2,
					get_priority_at(input, i - 2));
			}
			else
			{
				add_token(&tokens, TOKEN_REDIR_OUT, ">", -1, i - 1,
					get_priority_at(input, i));
				i++;
			}
		}
		else if (input[i] == '&' && is_in_quote_at(input, i) == QUOTE_NONE)
		{
			if (input[i + 1] == '&')
			{
				i += 2;
				if (input[i] == '&')
				{
					printf("Erreur de syntaxe : TRIPLE AND\n");
					return (NULL);
				}
				add_token(&tokens, TOKEN_AND, "&&", -1, i - 2,
					get_priority_at(input, i - 2));
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

void	init_all_index(t_token *tokens, t_token *args, t_token *quoted)
{
	int		min;
	t_token	*tmp;
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
	while (i < size)
	{
		min = INT_MAX;
		tokens = head_tokens;
		while (tokens)
		{
			if (tokens->index < min && tokens->num < 0)
			{
				tmp = tokens;
				min = tokens->index;
			}
			tokens = tokens->next;
		}
		args = head_args;
		while (args)
		{
			if (args->index < min && args->num < 0)
			{
				tmp = args;
				min = args->index;
			}
			args = args->next;
		}
		quoted = head_quoted;
		while (quoted)
		{
			if (quoted->index < min && quoted->num < 0)
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

int	verif_arg(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] != ' ')
			return (1);
		i++;
	}
	return (0);
}

t_command	*create_command(char **argv, unsigned int priority)
{
	t_command	*command;

	command = safe_malloc(sizeof(t_command));
	ft_bzero(command, sizeof(t_command));
	command->argv = argv;
	command->priority = priority;
	return (command);
}

t_list	*create_final_lst(t_token *keywords, t_list *args)
{
	t_list	*lst;
	t_list	*current;
	int		index;

	lst = NULL;
	index = ft_lstsize(args);
	while (index > 0)
	{
		current = ft_lstnew(args->content);
		args = args->next;
		if (keywords)
		{
			current->next = ft_lstnew(keywords);
			keywords = keywords->next;
		}
		ft_lstadd_back(&lst, current);
		index--;
	}
	return (lst);
}

void	lst_add_before_last(t_list **lst, t_list *node)
{
	t_list	*current;
	t_list	*prev;

	if (ft_lstsize(*lst) <= 1)
	{
		current = *lst;
		if (current)
			current->next = NULL;
		node->next = current;
		*lst = node;
	}
	else
	{
		current = *lst;
		prev = NULL;
		while (current && current->next)
		{
			prev = current;
			current = current->next;
		}
		if (prev)
			prev->next = node;
		node->next = current;
		current->next = NULL;
	}
}

t_list	*get_before_last(t_list *head)
{
	t_list	*current;

	current = head;
	while (current && current->next)
	{
		current = current->next;
	}
	return (current);
}

t_btree	*create_redirection_node(t_list **head, t_list *lst, bool doubled,
		t_redirection_types type)
{
	t_btree	*node;
	t_list	*prev;

	node = btree_create_node(BTREE_REDIRECTION_TYPE);
	node->content = safe_malloc(sizeof(t_btree_redir_node));
	ft_bzero(node->content, sizeof(t_btree_redir_node));
	((t_btree_redir_node *)node->content)->error = REDIRECTION_NO_ERROR;
	((t_btree_redir_node *)node->content)->type = type;
	((t_btree_redir_node *)node->content)->doubled = doubled;
	if (lst->next && ((t_token *)lst->next->content)->argv)
	{
		if (type == REDIRECTION_HERE_DOC_TYPE)
			((t_btree_redir_node *)node->content)->limiter = ((t_token *)lst->next->content)->argv[0];
		else
			((t_btree_redir_node *)node->content)->file = ((t_token *)lst->next->content)->argv[0];
		if (((t_token *)lst->next->content)->type == TOKEN_WORD)
			((t_token *)lst->next->content)->type = TOKEN_EOF;
		prev = get_before_last(*head);
		if (prev && ((t_btree *)prev->content)->type == BTREE_COMMAND_TYPE)
		{
			((t_command *)((t_btree *)prev->content)->content)->argv = add_tab_to_tab(((t_command *)((t_btree *)prev->content)->content)->argv,
					((t_token *)lst->next->content)->argv + 1);
		}
		else if ((type == REDIRECTION_IN_TYPE
				|| type == REDIRECTION_HERE_DOC_TYPE)
			&& ((t_token *)lst->next->content)->argv[1])
		{
			prev = ft_lstnew(btree_create_node(BTREE_COMMAND_TYPE));
			((t_btree *)prev->content)->content = create_command(add_tab_to_tab(NULL,
						((t_token *)lst->next->content)->argv + 1),
					((t_token *)lst->content)->priority);
			ft_lstadd_back(head, prev);
		}
	}
	return (node);
}

t_list	*create_btree_nodes_lst(t_list *lst)
{
	t_list	*head;
	t_list	*current;

	head = NULL;
	while (lst)
	{
		current = NULL;
		if (((t_token *)lst->content)->type == TOKEN_OR)
			current = ft_lstnew(btree_create_node(BTREE_OR_TYPE));
		else if (((t_token *)lst->content)->type == TOKEN_AND)
			current = ft_lstnew(btree_create_node(BTREE_AND_TYPE));
		else if (((t_token *)lst->content)->type == TOKEN_PIPE)
			current = ft_lstnew(btree_create_node(BTREE_PIPE_TYPE));
		else if (((t_token *)lst->content)->type == TOKEN_REDIR_IN)
		{
			current = ft_lstnew(create_redirection_node(&head, lst, false,
						REDIRECTION_IN_TYPE));
			lst_add_before_last(&head, current);
		}
		else if (((t_token *)lst->content)->type == TOKEN_REDIR_OUT)
		{
			current = ft_lstnew(create_redirection_node(&head, lst, false,
						REDIRECTION_OUT_TYPE));
			ft_lstadd_back(&head, current);
		}
		else if (((t_token *)lst->content)->type == TOKEN_APPEND)
		{
			current = ft_lstnew(create_redirection_node(&head, lst, true,
						REDIRECTION_OUT_TYPE));
			ft_lstadd_back(&head, current);
		}
		else if (((t_token *)lst->content)->type == TOKEN_HEREDOC)
		{
			current = ft_lstnew(create_redirection_node(&head, lst, false,
						REDIRECTION_HERE_DOC_TYPE));
			lst_add_before_last(&head, current);
		}
		else if (((t_token *)lst->content)->type != TOKEN_EOF && lst->content
			&& ((t_token *)lst->content)->argv)
		{
			current = ft_lstnew(btree_create_node(BTREE_COMMAND_TYPE));
			((t_btree *)current->content)->content = create_command(((t_token *)lst->content)->argv,
					((t_token *)lst->content)->priority);
		}
		if (current)
		{
			((t_btree *)current->content)->priority = ((t_token *)lst->content)->priority;
			if (((t_btree *)current->content)->type != BTREE_REDIRECTION_TYPE)
				ft_lstadd_back(&head, current);
		}
		lst = lst->next;
	}
	return (head);
}

t_btree	*get_last_condition(t_list *lst, unsigned int priority)
{
	t_list	*current;

	current = NULL;
	while (lst)
	{
		if ((((t_btree *)lst->content)->type == BTREE_AND_TYPE
				|| ((t_btree *)lst->content)->type == BTREE_OR_TYPE)
			&& ((t_btree *)lst->content)->priority == priority)
			current = lst;
		lst = lst->next;
	}
	if (current)
		return (current->content);
	return (NULL);
}

bool	remain_node_for_priority(t_list *lst, unsigned int priority)
{
	t_list	*current;

	current = NULL;
	while (lst)
	{
		if ((((t_btree *)lst->content)->type == BTREE_AND_TYPE
				|| ((t_btree *)lst->content)->type == BTREE_OR_TYPE)
			&& ((t_btree *)lst->content)->priority == priority)
			current = lst;
		lst = lst->next;
	}
	if (current)
		return (true);
	return (false);
}

t_list	*left_truncate_lst(t_list *lst, t_btree *stop)
{
	t_list	*new_lst;

	new_lst = NULL;
	while (lst && lst->content != stop)
	{
		ft_lstadd_back(&new_lst, ft_lstnew(lst->content));
		lst = lst->next;
	}
	return (new_lst);
}

t_list	*right_truncate_lst(t_list *lst, t_btree *stop)
{
	t_list	*new_lst;

	new_lst = NULL;
	while (lst && lst->content != stop)
		lst = lst->next;
	if (lst)
		lst = lst->next;
	while (lst)
	{
		ft_lstadd_back(&new_lst, ft_lstnew(lst->content));
		lst = lst->next;
	}
	return (new_lst);
}

t_btree	*create_final_tree(t_list *remaning_nodes, unsigned int priority)
{
	t_btree	*node;

	if (!remaning_nodes)
		return (NULL);
	if (!remain_node_for_priority(remaning_nodes, priority))
		priority++;
	node = get_last_condition(remaning_nodes, priority);
	if (!node)
	{
		node = remaning_nodes->content;
		node->left = create_final_tree(remaning_nodes->next, priority);
		if (node->left)
			node->left->prev = node;
	}
	else
	{
		node->right = create_final_tree(right_truncate_lst(remaning_nodes,
					node), priority);
		if (node->right)
			node->right->prev = node;
		node->left = create_final_tree(left_truncate_lst(remaning_nodes, node),
				priority);
		if (node->left)
			node->left->prev = node;
	}
	return (node);
}

int	ft_number_quote(char *str)
{
	int		i;
	char	flag;
	int		count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if ((str[i] == '"' || str[i] == '\''))
		{
			flag = str[i];
			count++;
			i++;
			while (str[i] != flag && str[i])
				i++;
			count++;
		}
		i++;
	}
	return (count);
}

int	check_only_quote(char *str)
{
	int		i;
	char	flag;

	i = 0;
	if (str[i] == '"' || str[i] == '\'')
		flag = str[i];
	else
		return (0);
	while (str[i])
	{
		if (str[i] != flag)
			return (0);
		i++;
	}
	return (1);
}
void	extract_quote(t_token **head, t_token *quoted)
{
	char	*str;
	int		size;
	int		i;
	int		j;
	char	flag;

	while (quoted)
	{
		if (check_only_quote(quoted->value) == 1)
		{
			quoted = quoted->next;
			continue ;
		}
		i = ft_number_quote(quoted->value);
		j = 0;
		flag = 0;
		size = ft_strlen(quoted->value);
		str = safe_malloc(sizeof(char) * (size + 1) - (i));
		i = 0;
		while (quoted->value[i])
		{
			if ((quoted->value[i] == '"' || quoted->value[i] == '\''))
			{
				flag = quoted->value[i];
				i++;
				while (quoted->value[i] != flag && quoted->value[i])
				{
					str[j] = quoted->value[i];
					i++;
					j++;
				}
				i++;
			}
			else if (quoted->value[i])
			{
				str[j] = quoted->value[i];
				i++;
				j++;
			}
		}
		str[j] = '\0';
		add_token(head, TOKEN_QUOTED, str, -1, quoted->index,
			get_priority_at(str, quoted->index));
		quoted = quoted->next;
	}
}

void	parse_line(t_minishell *data, char *line)
{
	t_token	*keywords;
	t_token	*args;
	t_token	*half_quoted;
	t_token	*quoted;
	t_list	*new_args;
	t_btree	*tree;
	t_list	*lst;
	char	quote;

	quote = verif_quote(line);
	if (quote == '\'')
		return (data->exit_code = 2, ft_fprintf(STDERR_FILENO,
				ERROR_SINGLE_QUOTE), (void)0);
	else if (quote == '"')
		return (data->exit_code = 2, ft_fprintf(STDERR_FILENO,
				ERROR_DOUBLE_QUOTE), (void)0);
	if (check_priorities(line))
		return (data->exit_code = 2, (void)0);
	half_quoted = NULL;
	args = extract_arg(line, &half_quoted);
	keywords = tokenize(data, line);
	quoted = NULL;
	extract_quote(&quoted, half_quoted);
	init_all_index(keywords, args, quoted);
	new_args = NULL;
	create_lst_args(&new_args, keywords, args, quoted);
	lst = create_final_lst(keywords, new_args);
	lst = create_btree_nodes_lst(lst);
	tree = create_final_tree(lst, 0);
	data->execution_tree = tree;
}
