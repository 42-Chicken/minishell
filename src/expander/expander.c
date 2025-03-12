/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 10:21:55 by rguigneb          #+#    #+#             */
/*   Updated: 2025/03/12 09:04:51 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "define.h"
#include "minishell.h"

t_e_quote_type	is_in_quote_at(char *str, int index)
{
	int				i;
	t_e_quote_type	quote;

	i = -1;
	quote = QUOTE_NONE;
	while (str[++i] && i <= index)
	{
		if (str[i] == '"')
		{
			if (quote == QUOTE_DOUBLED)
				quote = QUOTE_NONE;
			else if (quote == QUOTE_NONE && ft_strchr(str + i + 1, '"'))
				quote = QUOTE_DOUBLED;
		}
		else if (str[i] == '\'')
		{
			if (quote == QUOTE_SIMPLE)
				quote = QUOTE_NONE;
			else if (quote == QUOTE_NONE && ft_strchr(str + i + 1, '\''))
				quote = QUOTE_SIMPLE;
		}
	}
	return (quote);
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
				|| ft_isspace(str[i + 1])) && is_in_quote_at(str,
				i) != QUOTE_SIMPLE)
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

static char	*expand_from_env(t_minishell *data, char *str)
{
	size_t	i;
	char	*name;
	char	*dollar_var_name;
	char	*inside;

	i = -1;
	while (data->envp[++i])
	{
		name = get_var_name((char *)data->envp[i]);
		dollar_var_name = ft_strjoin("$", name);
		inside = ft_strnstr(str, dollar_var_name, ft_strlen(str));
		if (!inside)
			continue ;
		if (is_in_quote_at(str, inside - str) != QUOTE_SIMPLE)
			str = ft_strreplace_at_index(str, inside - str,
					ft_strlen(dollar_var_name), (char *)get_env(data->envp,
						name));
	}
	return (str);
}

char	*expand(t_minishell *data, char *str)
{
	char	*result;

	if (!str)
		return (NULL);
	result = ft_strdup(str);
	if (result && ft_strnstr(result, EXPANDER_EXIT_CODE_PATERN,
			ft_strlen(result)))
		result = ft_strreplace(result, EXPANDER_EXIT_CODE_PATERN,
				ft_itoa(data->exit_code));
	if (result && ft_strnstr(result, EXPANDER_PID_PATERN, ft_strlen(result)))
		result = ft_strreplace(result, EXPANDER_PID_PATERN, GIGACHAD);
	result = expand_from_env(data, result);
	result = handle_tild(data, result);
	result = handle_wildcard(data, result);
	return (result);
}
