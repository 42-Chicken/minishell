/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 08:30:12 by rguigneb          #+#    #+#             */
/*   Updated: 2025/02/26 10:19:07 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "minishell.h"

char	*get_var_value(char *str)
{
	char	*start;

	start = ft_strchr(str, '=');
	if (!start)
		return (NULL);
	start = ft_substr(str, start - str + 1, ft_strlen(str));
	return (start);
}

char	*get_var_name(char *str)
{
	char	*start;
	char	*plus;

	plus = NULL;
	if (str && ft_strlen(str) > 1)
		plus = ft_strrchr(str, '+');
	if (str && plus && plus[1] == '=')
	{
		start = ft_strchr(str, '=');
		if (!start)
			return (str);
		str = ft_substr(str, 0, start - str - 1);
	}
	else
	{
		start = ft_strchr(str, '=');
		if (!start)
			return (str);
		str = ft_substr(str, 0, start - str);
	}
	return (str);
}

char	*get_formatted_env_line(char *line)
{
	char	*result;
	char	*value;

	result = get_var_name(line);
	value = get_var_value(line);
	if (!value)
		return (result);
	result = ft_strjoin(result, ft_strdup("=\""));
	result = ft_strjoin(result, value);
	result = ft_strjoin(result, ft_strdup("\""));
	return (result);
}
