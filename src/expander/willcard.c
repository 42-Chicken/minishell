/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   willcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 08:32:08 by rguigneb          #+#    #+#             */
/*   Updated: 2025/03/11 15:34:34 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "define.h"
#include "minishell.h"

bool	ft_fnmatch(char *patern, char *str)
{
	if (!patern || !str)
		return (false);
	if (patern[0] == 0)
		return (str[0] == 0);
	if (str[0] == 0)
		return (ft_strncmp(patern, "*", ft_strlen(patern)) == 0);
	if (patern[0] == '*')
	{
		if (ft_fnmatch(patern + 1, str))
			return (true);
		if (ft_fnmatch(patern, str + 1))
			return (true);
		return (ft_fnmatch(patern + 1, str + 1));
	}
	if (patern[0] == str[0])
		return (ft_fnmatch(patern + 1, str + 1));
	return (false);
}

char	*get_patern(char *str, size_t i)
{
	size_t	end;

	end = 0;
	while (i > 0 && !ft_isspace(str[i - 1]))
		i--;
	while ((str + i)[end] && !ft_isspace((str + i)[end]))
		end++;
	return (ft_substr(str, i, end));
}

char	*replace_patern(char *str, size_t i, char *replacment)
{
	size_t	end;

	end = 0;
	while (i > 0 && !ft_isspace(str[i - 1]))
		i--;
	while ((str + i)[end] && !ft_isspace((str + i)[end]))
		end++;
	str = ft_strreplace_at_index(str, i, end, replacment);
	return (str);
}

char	*filter_wildcard(char *str, size_t i)
{
	size_t	y;
	char	**dirs_names;
	char	*result;
	char	*patern;

	y = -1;
	patern = get_patern(str, i);
	result = ft_strdup("");
	dirs_names = get_dir_files_into_array((char *)".");
	while (dirs_names && dirs_names[++y])
	{
		if (ft_fnmatch(patern, dirs_names[y]))
		{
			if (startswith(dirs_names[y], ".") && !startswith(patern, "."))
				continue ;
			if (ft_strlen(result) > 0)
				result = ft_strjoin(result, " ");
			result = ft_strjoin(result, dirs_names[y]);
		}
	}
	if (ft_strlen(result) != 0)
		result = replace_patern(str, i, result);
	else
		result = replace_patern(str, i, patern);
	return (result);
}

char	*handle_wildcard(t_minishell *data, char *str)
{
	size_t	i;
	char	*result;

	i = 0;
	(void)data;
	if (!str || !ft_strchr(str, '*'))
		return (str);
	result = str;
	while (result[i])
	{
		if (result[i] == '*' && is_in_quote_at(result, i) == QUOTE_NONE)
			result = filter_wildcard(result, i);
		i++;
	}
	return (result);
}
