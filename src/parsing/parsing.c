/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efranco <efranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 14:28:58 by rguigneb          #+#    #+#             */
/*   Updated: 2025/03/06 16:17:07 by efranco          ###   ########.fr       */
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

t_list	*create_lst_args(t_token *keywords, t_token *args, t_token *quoted)
{
	t_list	*head;
	t_list	*lst;
	t_token	*current;
	int		index;
	int		limit;
	int		max;
	char	**tab;
	int		i;

	head = NULL;
	lst = NULL;
	index = 0;
	max = get_max_lst(keywords, args, quoted);
	while (index <= max)
	{
		current = get_index_lst(index, keywords, args, quoted);
		limit = 0;
		while (current && (current->type == TOKEN_WORD
				|| current->type == TOKEN_QUOTED))
		{
			limit++;
			current = get_index_lst(index + limit, keywords, args, quoted);
		}
		if (limit > 0)
		{
			i = 0;
			tab = safe_malloc(sizeof(char *) * (limit + 1));
			while (i < limit)
			{
				current = get_index_lst(index, keywords, args, quoted);
				tab[i] = ft_strdup(current->value);
				i++;
				index++;
			}
			tab[limit] = NULL;
			lst = ft_lstnew(tab);
			ft_lstadd_back(&head, lst);
		}
		else
			index++;
	}
	return (head);
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

t_list	*get_organized_index(t_list *organized, int index)
{
	int	i;

	i = 0;
	printf("index : %d\n", index);
	while (organized && i < index)
		organized = organized->next;
	return (organized);
}
int	is_and_or(t_token *keywords, int limit)
{
	int	i;

	i = -1;
	while (keywords)
	{
		if (limit > keywords->num && (keywords->type == TOKEN_AND || keywords->type == TOKEN_OR))
			i = keywords->num;
		keywords = keywords->next;
	}
	return (i);
}
t_token *search_last_and_or(t_token *keywords)
{
	t_token	*last;

	last = NULL;
	while(keywords)
	{
		if (keywords->type == TOKEN_AND || keywords->type == TOKEN_OR)
			last = keywords;
		keywords = keywords->next;
	}
	return (last);
}

t_command *create_command(char **argv)
{
	t_command *command;

	command = safe_malloc(sizeof(t_command));
	ft_bzero(command, sizeof(t_command));
	command->argv = argv;
	return (command);
}
void split_list(t_list *args, t_token *keywords, t_token *last, t_direction *direct)
{
    t_token *tmp_keywords = keywords;
    t_list *tmp_args = args;

    direct->left_keyword = keywords;
    direct->left_arg = args;

    while (tmp_keywords && tmp_keywords != last)
    {
        tmp_args = tmp_args->next;
        tmp_keywords = tmp_keywords->next;
    }
    if (tmp_keywords)
    {
        direct->right_arg = tmp_args->next;
        direct->right_keyword = tmp_keywords->next;
    }
    else
    {
        direct->right_arg = NULL;
        direct->right_keyword = NULL;
    }
}

t_btree	*convert_to_btree(t_list *args, t_token *keywords, t_direction *direct)
{
	t_btree 	*tree;
	t_token 	*last;
	t_direction new_direct;

	new_direct.left_arg = NULL;
	new_direct.left_keyword = NULL;
	new_direct.right_arg = NULL;
	new_direct.right_keyword = NULL;
	last = search_last_and_or(keywords);
	printf("%s\n", last->value);
	if (!last)
	{
		if (!args)
			return (NULL);
		tree = btree_create_node(BTREE_COMMAND_TYPE);
		tree->content = create_command(args->content);
		return(tree);
	}
	if (last->type == TOKEN_AND)
		tree = btree_create_node(BTREE_AND_TYPE);
	if (last->type == TOKEN_OR)
		tree = btree_create_node(BTREE_OR_TYPE);
	split_list(args, keywords, last, &new_direct);
	tree->left = convert_to_btree(new_direct.left_arg, new_direct.left_keyword, &new_direct);
	tree->right = convert_to_btree(new_direct.right_arg, new_direct.right_keyword, &new_direct);
	return (tree);
}

void	parse_line(t_minishell *data, char *line)
{
	t_token	*keywords;
	t_token	*args;
	t_token	*quoted;
	t_list	*new_args;
	t_btree	*tree;
	t_direction	direct;
	int		i;

	quoted = NULL;
	keywords = tokenize(line);
	args = extract_arg(line, &quoted);
	if (args == NULL)
	{
		ft_fprintf(STDERR_FILENO, "Erreur de quote\n");
		return ;
	}
	init_all_index(keywords, args, quoted);
	new_args = create_lst_args(keywords, args, quoted);
	direct.left_arg = NULL;
	direct.left_keyword = NULL;
	direct.right_arg = NULL;
	direct.right_keyword = NULL;
	tree = convert_to_btree(new_args, keywords, &direct);
	printf("right : %p\n", tree->right);
	printf("left : %p\n", tree->left);
	data->execution_tree = tree;
}


// while (new_args)
// {
// 	i = 0;
// 	while (((char **)new_args->content)[i])
// 		printf("%s", ((char **)new_args->content)[i++]);
// 		printf("\n");
// 		new_args = new_args->next;
// 	}
	// while (quoted)
	// {
		// 	printf("Quoted : [%s] | Index : [%d]\n", quoted->value, quoted->num);
		// 	quoted = quoted->next;
		// }
		// while (keywords)
		// {
			// 	printf("Token : [%s] | Index : [%d]\n", keywords->value, keywords->num);
			// 	keywords = keywords->next;
			// }
			// while (args)
			// {
				// 	printf("arguments : [%s] | Index : [%d]\n", args->value, args->num);
				// 	args = args->next;
				// }




				// t_btree	*convert_to_btree(t_btree **tree, int index, t_token *keywords,
				// 		t_token *args, t_token *quoted)
				// {
				// 	t_token		*current;
				// 	t_btree		*node;
				// 	t_command	*command;
				// 	static int	args_index = -1;
				// 	t_list		*organized;

				// 	organized = create_new_args(keywords, args, quoted);
				// 	if (args_index == -1)
				// 	{
				// 		args_index = ft_lstsize(organized);
				// 	}
				// 	current = get_index_lst(index, keywords, args, quoted);
				// 	node = NULL;
				// 	if (current->type == TOKEN_AND || current->type == TOKEN_OR)
				// 	{
				// 		if (!tree)
				// 			*tree = btree_create_node(TOKEN_OR);
				// 		(*tree)->right = convert_to_btree(*tree, index + 1, keywords, args, quoted);
				// 	}
				// 	else
				// 	{
				// 		// char **
				// 		if (current->type == TOKEN_PIPE)
				// 			node = btree_create_node(BTREE_PIPE_TYPE);
				// 		else
				// 		{
				// 			node = btree_create_node(BTREE_COMMAND_TYPE);
				// 			command = safe_malloc(sizeof(t_command));
				// 			ft_bzero(command, sizeof(t_command));
				// 			command->argv = get_organized_index(organized, args_index--);
				// 			node->content = command;
				// 		}
				// 		if (current->type == TOKEN_WORD)
				// 		{
				// 			node = btree_create_node(BTREE_REDIRECTION_TYPE);
				// 			node->content = safe_malloc(sizeof(t_btree_redir_node));
				// 			((t_btree_redir_node *)node->content)->doubled = true;
				// 			((t_btree_redir_node *)node->content)->file = true;
				// 		}
				// 		if (current->type == TOKEN_APPEND)
				// 		{
				// 			node = btree_create_node(BTREE_REDIRECTION_TYPE);
				// 			node->content = safe_malloc(sizeof(t_btree_redir_node));
				// 			((t_btree_redir_node*)node->content)->doubled = true;
				// 			((t_btree_redir_node*)node->content)->file = true;
				// 		}
				// 		return (node);
				// 	}
				// }
