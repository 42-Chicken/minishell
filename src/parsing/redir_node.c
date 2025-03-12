/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_node.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:20:12 by rguigneb          #+#    #+#             */
/*   Updated: 2025/03/12 15:20:17 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static bool	is_valid_redir(t_redirection_types type, t_token *lst_next_content)
{
	return ((type == REDIRECTION_IN_TYPE || type == REDIRECTION_HERE_DOC_TYPE)
		&& lst_next_content->argv[1]);
}

static void	handle_prev(t_list **head, t_list *lst, t_token *lst_next_content,
		t_redirection_types type)
{
	t_list	*prev;
	t_btree	*prev_node;

	prev = get_before_last(*head);
	prev_node = ((t_btree *)prev->content);
	if (prev && prev_node->type == BTREE_COMMAND_TYPE)
	{
		((t_command *)prev_node->content)->argv = \
			add_tab_to_tab(((t_command *)prev_node->content)->argv,
				lst_next_content->argv + 1);
	}
	else if (is_valid_redir(type, lst_next_content))
	{
		prev = ft_lstnew(btree_create_node(BTREE_COMMAND_TYPE));
		prev_node->content = create_command(add_tab_to_tab(NULL,
					lst_next_content->argv + 1),
				((t_token *)lst->content)->priority);
		ft_lstadd_back(head, prev);
	}
}

t_btree	*create_redirection_node(t_list **head, t_list *lst, bool doubled,
		t_redirection_types type)
{
	t_btree	*node;
	t_token	*lst_next_content;

	node = btree_create_node(BTREE_REDIRECTION_TYPE);
	node->content = safe_malloc(sizeof(t_btree_redir_node));
	ft_bzero(node->content, sizeof(t_btree_redir_node));
	((t_btree_redir_node *)node->content)->error = REDIRECTION_NO_ERROR;
	((t_btree_redir_node *)node->content)->type = type;
	((t_btree_redir_node *)node->content)->doubled = doubled;
	lst_next_content = ((t_token *)lst->next->content);
	if (lst->next && lst_next_content->argv)
	{
		if (type == REDIRECTION_HERE_DOC_TYPE)
			((t_btree_redir_node *)node->content)->limiter = \
				lst_next_content->argv[0];
		else
			((t_btree_redir_node *)node->content)->file = \
			lst_next_content->argv[0];
		if (lst_next_content->type == TOKEN_WORD)
			lst_next_content->type = TOKEN_EOF;
		handle_prev(head, lst, lst_next_content, type);
	}
	return (node);
}
