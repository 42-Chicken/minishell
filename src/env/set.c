/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 08:54:01 by rguigneb          #+#    #+#             */
/*   Updated: 2025/02/12 12:50:48 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "minishell.h"

void	set_env(const char **envp, const char *variable, char *value)
{
	char	*new_line;
	int		index;

	if (!envp || !*envp || !variable)
		return ;
	index = get_env_index(envp, variable);
	if (index == -1)
		return ;
	new_line = ft_strjoin(variable, "=");
	new_line = ft_strjoin(new_line, value);
	envp[index] = new_line;
}
