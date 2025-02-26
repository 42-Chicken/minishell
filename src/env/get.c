/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 08:54:01 by rguigneb          #+#    #+#             */
/*   Updated: 2025/02/26 10:45:17 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "minishell.h"

int	custom_get_var_env_index(const char **envp, const char *variable)
{
	int	i;

	i = -1;
	if (!envp || !*envp || !variable)
		return (-1);
	while (envp[++i])
	{
		if (ft_strchr(envp[i], '='))
		{
			if ((int)ft_strlen(variable) == ft_strchr(envp[i], '=') - envp[i]
				&& ft_strncmp(envp[i], variable, ft_strchr(envp[i], '=')
					- envp[i]) == 0)
				return (i);
		}
		else
		{
			if (ft_strlen(envp[i]) == ft_strlen(variable) && ft_strncmp(envp[i],
					variable, ft_strlen(variable)) == 0)
				return (i);
		}
	}
	return (-1);
}

static char	*get_target_string(const char *variable)
{
	char	*target;
	size_t	len;

	len = ft_strlen(variable);
	target = (char *)malloc(sizeof(char) * (len + 1) + 1);
	if (!target)
		return (NULL);
	ft_strlcpy(target, variable, len + 1);
	target[len] = '=';
	target[len + 1] = '\0';
	return (target);
}

int	get_raw_env_index(const char **envp, const char *variable)
{
	int	i;

	i = -1;
	if (!envp || !*envp || !variable)
		return (-1);
	while (envp[++i])
		if (ft_strncmp(envp[i], variable, ft_strlen(envp[i])) == 0)
			return (i);
	return (-1);
}

int	get_env_index(const char **envp, const char *variable)
{
	int		i;
	char	*target;

	i = -1;
	if (!envp || !*envp || !variable)
		return (-1);
	target = get_target_string(variable);
	if (!target)
		return (-1);
	while (envp[++i])
		if (ft_strncmp(envp[i], target, ft_strlen(target)) == 0)
			return (free(target), i);
	return (free(target), -1);
}

int	get_env_length(const char **envp)
{
	int	i;

	i = 0;
	while (envp && envp[i])
		i++;
	return (i);
}

const char	*get_env(const char **envp, const char *variable)
{
	int	index;

	(void)envp;
	if (!envp || !*envp || !variable)
		return (NULL);
	index = get_env_index(envp, variable);
	if (index != -1)
		return ((char *)((char *)envp[index] + ft_strlen(variable) + 1));
	return (NULL);
}
