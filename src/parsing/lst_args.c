/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:49:37 by rguigneb          #+#    #+#             */
/*   Updated: 2025/03/13 08:40:55 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	process_token(t_token *current, char ***tab, int *priority)
{
	*priority = current->priority;
	if (current->type == TOKEN_QUOTED)
		*tab = add_to_tab(*tab, current->value);
	else if (current->type == TOKEN_WORD && line_is_empty(current) == 0)
		*tab = add_tab_to_tab(*tab, ft_split(current->value, SPACES));
}

void	add_new_token(t_list **head, char ***tab, int priority)
{
	t_token	*new_token;

	new_token = safe_malloc(sizeof(t_token));
	ft_bzero(new_token, sizeof(t_token));
	new_token->type = TOKEN_WORD;
	new_token->argv = *tab;
	new_token->priority = priority;
	ft_lstadd_back(head, ft_lstnew(new_token));
	*tab = NULL;
}

void	create_lst_args(t_list **head, t_token *keywords, t_token *args,
		t_token *quoted)
{
	char	**tab;
	int		index;
	int		priority;
	int		max;
	t_token	*current;

	tab = NULL;
	index = 0;
	priority = 0;
	max = get_max_lst(keywords, args, quoted);
	while (index <= max)
	{
		current = get_index_lst(index, keywords, args, quoted);
		while (current && (current->type == TOKEN_WORD
				|| current->type == TOKEN_QUOTED))
		{
			process_token(current, &tab, &priority);
			current = get_index_lst(++index, keywords, args, quoted);
		}
		if (current && is_keywords(current))
			add_new_token(head, &tab, priority);
		index++;
	}
	if (tab)
		add_new_token(head, &tab, priority);
}
