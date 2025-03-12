/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyword.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:25:21 by rguigneb          #+#    #+#             */
/*   Updated: 2025/03/12 14:41:02 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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
