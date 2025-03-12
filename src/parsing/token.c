/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:27:33 by rguigneb          #+#    #+#             */
/*   Updated: 2025/03/12 14:47:01 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

t_token	*add_token(t_token **head, t_e_token_type type, char *value, int i,
		int h, unsigned int priority)
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
