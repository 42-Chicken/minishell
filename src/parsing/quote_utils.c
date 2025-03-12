/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:43:58 by rguigneb          #+#    #+#             */
/*   Updated: 2025/03/12 14:44:31 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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
