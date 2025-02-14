/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 10:54:00 by rguigneb          #+#    #+#             */
/*   Updated: 2025/02/14 13:36:36 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "paths.h"

char	*get_home_path(t_minishell *data)
{
	char	*i;
	char	*path;

	path = (char *)get_env(data->envp, "HOME");
	if (!path)
	{
		path = ft_strnstr(data->started_path, "/home/",
				ft_strlen(data->started_path));
		if (path)
		{
			i = ft_strchr(path + ft_strlen("/home/"), '/');
			if (i)
				path = ft_substr(path, 0, i - path);
		}
	}
	if (!path)
		path = (char *)"~";
	return (path);
}

char	*get_current_path(t_minishell *data)
{
	char	*path;

	path = (char *)get_env(data->envp, "PWD");
	if (!path)
		path = (char *)data->started_path;
	return (path);
}
