/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 10:21:55 by rguigneb          #+#    #+#             */
/*   Updated: 2025/03/03 08:44:37 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "define.h"
#include "minishell.h"

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
	result = handle_wildcard(data, result);
	if (result && ft_strnstr(result, "$?", ft_strlen(result)))
		result = ft_strreplace(result, "$?", ft_itoa(data->exit_code));
	return (result);
}
