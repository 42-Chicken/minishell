/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 10:21:55 by rguigneb          #+#    #+#             */
/*   Updated: 2025/02/28 14:58:25 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "define.h"
#include "minishell.h"

static char	*get_dir_files(t_minishell *data)
{
	DIR				*dir;
	struct dirent	*current;
	char			*result;

	(void)data;
	dir = opendir(".");
	current = NULL;
	result = ft_strdup("");
	if (!dir)
		return (result);
	current = readdir(dir); // redo this
	while (current)
	{
		if (current->d_name[0] != '.' && !is_same_str(current->d_name, ".."))
		{
			result = ft_strjoin(result, " ");
			result = ft_strjoin(result, current->d_name);
		}
		current = readdir(dir);
	}
	return (result);
}

static char	*handle_tild(t_minishell *data, char *str)
{
	size_t	i;
	char	*result;

	i = -1;
	result = NULL;
	while (str[++i])
	{
		if (str[i] == HOME_DIRECTORY_REPRESENTATION[0] && (i == 0
				|| ft_isspace(str[i - 1])) && (!str[i + 1] || str[i + 1] == '/'
				|| ft_isspace(str[i + 1])))
		{
			if (result)
				return (handle_tild(data, result));
			result = ft_substr(str, 0, i);
			result = ft_strjoin(result, (char *)get_env(data->envp, ENV_HOME));
			result = ft_strjoin(result, str + i + 1);
		}
	}
	if (result)
		return (result);
	return (str);
}

static char	*handle_wildcard(t_minishell *data, char *str)
{
	size_t	i;
	char	*result;

	i = -1;
	result = NULL;
	while (str[++i])
	{
		if (str[i] == HOME_DIRECTORY_REPRESENTATION[0] && (i == 0
				|| ft_isspace(str[i - 1])) && (!str[i + 1] || str[i + 1] == '/'
				|| ft_isspace(str[i + 1])))
		{
			if (result)
				return (handle_tild(data, result));
			result = ft_substr(str, 0, i);
			result = ft_strjoin(result, (char *)get_env(data->envp, ENV_HOME));
			result = ft_strjoin(result, str + i + 1);
		}
	}
	if (result)
		return (result);
	return (str);
}

char	*expand(t_minishell *data, char *str)
{
	size_t	i;
	char	*name;
	char	*result;

	i = -1;
	if (!str)
		return (NULL);
	result = ft_strdup(str);
	while (data->envp[++i])
	{
		name = get_var_name((char *)data->envp[i]);
		result = ft_strreplace(result, ft_strjoin("$", name),
				(char *)get_env(data->envp, name));
	}
	result = handle_tild(data, result);
	if (result && ft_strchr(result, '*'))
		result = ft_strreplace(result, "*", get_dir_files(data));
	return (result);
}
