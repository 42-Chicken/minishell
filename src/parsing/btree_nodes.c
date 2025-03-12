/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_nodes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:54:12 by rguigneb          #+#    #+#             */
/*   Updated: 2025/03/12 15:01:37 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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

static void	if_else_redir_nodes(t_list **head, t_list *lst, t_list **current)
{
	if (((t_token *)lst->content)->type == TOKEN_REDIR_IN)
	{
		(*current) = ft_lstnew(create_redirection_node(head, lst, false,
					REDIRECTION_IN_TYPE));
		lst_add_before_last(head, (*current));
	}
	else if (((t_token *)lst->content)->type == TOKEN_REDIR_OUT)
	{
		(*current) = ft_lstnew(create_redirection_node(head, lst, false,
					REDIRECTION_OUT_TYPE));
		ft_lstadd_back(head, (*current));
	}
	else if (((t_token *)lst->content)->type == TOKEN_APPEND)
	{
		(*current) = ft_lstnew(create_redirection_node(head, lst, true,
					REDIRECTION_OUT_TYPE));
		ft_lstadd_back(head, (*current));
	}
	else if (((t_token *)lst->content)->type == TOKEN_HEREDOC)
	{
		(*current) = ft_lstnew(create_redirection_node(head, lst, false,
					REDIRECTION_HERE_DOC_TYPE));
		lst_add_before_last(head, (*current));
	}
}

static void	handle_word_node(t_list *lst, t_list **current)
{
	if (((t_token *)lst->content)->type != TOKEN_EOF && lst->content
		&& ((t_token *)lst->content)->argv)
	{
		(*current) = ft_lstnew(btree_create_node(BTREE_COMMAND_TYPE));
		((t_btree *)(*current)->content)->content = create_command(((t_token *)lst->content)->argv,
				((t_token *)lst->content)->priority);
	}
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
		if_else_redir_nodes(&head, lst, &current);
		handle_word_node(lst, &current);
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
