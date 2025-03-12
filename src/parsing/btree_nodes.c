/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_nodes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:54:12 by rguigneb          #+#    #+#             */
/*   Updated: 2025/03/12 15:20:47 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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
		((t_btree *)(*current)->content)->content = \
		create_command(((t_token *)lst->content)->argv,
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
			((t_btree *)current->content)->priority = \
				((t_token *)lst->content)->priority;
			if (((t_btree *)current->content)->type != BTREE_REDIRECTION_TYPE)
				ft_lstadd_back(&head, current);
		}
		lst = lst->next;
	}
	return (head);
}
