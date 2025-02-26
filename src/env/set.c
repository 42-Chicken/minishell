/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 08:54:01 by rguigneb          #+#    #+#             */
/*   Updated: 2025/02/26 10:17:25 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "minishell.h"

void	remove_from_env_index(const char ***envp, int index)
{
	int		i;
	int		k;
	size_t	new_len;
	char	**new_env;

	i = 0;
	k = 0;
	if (!envp || !*envp || index < 0)
		return ;
	new_len = get_env_length(*envp);
	new_env = safe_malloc(sizeof(char *) * new_len);
	send_pointer_to_main_context(new_env);
	while (*envp && (*envp)[i])
	{
		if (i == index)
			i++;
		else
			new_env[k++] = (char *)(*envp)[i++];
	}
	new_env[k] = NULL;
	*envp = (const char **)new_env;
}

void	remove_from_env(const char ***envp, const char *variable)
{
	int		i;
	int		k;
	size_t	new_len;
	char	**new_env;

	i = 0;
	k = 0;
	if (!envp || !*envp || !variable)
		return ;
	new_len = get_env_length(*envp);
	new_env = safe_malloc(sizeof(char *) * new_len);
	send_pointer_to_main_context(new_env);
	while (*envp && (*envp)[i])
	{
		if (ft_strncmp(variable, (*envp)[i], ft_strlen(variable)) == 0)
			i++;
		else
			new_env[k++] = (char *)(*envp)[i++];
	}
	new_env[k] = NULL;
	*envp = (const char **)new_env;
}

void	add_to_env(const char ***envp, char *line)
{
	int		i;
	size_t	new_len;
	char	**new_env;

	i = 0;
	if (!envp || !*envp || !line)
		return ;
	new_len = get_env_length(*envp) + 2;
	new_env = safe_malloc(sizeof(char *) * new_len);
	send_pointer_to_main_context(new_env);
	new_env[new_len - 1] = NULL;
	while (*envp && (*envp)[i])
	{
		new_env[i] = (char *)(*envp)[i];
		i++;
	}
	new_env[i] = line;
	*envp = (const char **)new_env;
}

void	set_env(const char ***envp, const char *variable, char *value)
{
	char	*new_line;
	int		index;

	if (!envp || !variable)
		return ;
	index = custom_get_var_env_index(*envp, variable);
	new_line = ft_strjoin(variable, "=");
	if (!value && index != -1)
	{
		remove_from_env(envp, new_line);
		return ;
	}
	new_line = ft_strjoin(new_line, value);
	send_pointer_to_main_context(new_line);
	if (index == -1)
		add_to_env(envp, new_line);
	else
		(*envp)[index] = new_line;
}
