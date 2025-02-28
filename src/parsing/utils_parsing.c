/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efranco <efranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 11:10:17 by efranco           #+#    #+#             */
/*   Updated: 2025/02/28 12:09:42 by efranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

char	*ft_strndup(char *str, int n)
{
	char	*copy;
	int		i;

	i = 0;
	copy = safe_malloc(sizeof(char) * n + 1);
	while (str[i] && i < n)
	{
		copy[i] = str[i];
		i++;
	}
	copy[i] = '\0';
	return(copy);
}
int	ft_tokensize(t_token *lst)
{
	size_t	i;

	i = 0;
	while (lst != NULL)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}
