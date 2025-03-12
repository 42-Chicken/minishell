/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 14:28:58 by rguigneb          #+#    #+#             */
/*   Updated: 2025/03/12 14:41:05 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "define.h"
#include "minishell.h"
#include "parsing.h"
#include <limits.h>

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
