/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 08:54:01 by rguigneb          #+#    #+#             */
/*   Updated: 2025/02/12 12:33:59 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "minishell.h"

static char	*serialized_variable(const char *variable, const char *line)
{
	return ((char *)line + ft_strlen(variable) + 1);
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

const char	*get_env(const char *variable, const char **envp)
{
	size_t	i;
	char	*target;

	i = -1;
	if (!envp || !*envp || !variable)
		return (NULL);
	target = get_target_string(variable);
	while (envp[++i])
		if (ft_strncmp(envp[i], target, ft_strlen(target)) == 0)
			return (free(target), serialized_variable(variable, envp[i]));
	return (free(target), NULL);
}
