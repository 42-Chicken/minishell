/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 10:54:00 by rguigneb          #+#    #+#             */
/*   Updated: 2025/02/20 17:31:10 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "paths.h"

char	*get_current_folder_name(void)
{
	int		i;
	char	**path;
	char	current[MAX_PATH_LENGTH];
	char	*result;

	result = NULL;
	create_safe_memory_context();
	getcwd(current, MAX_PATH_LENGTH);
	path = ft_split(current, '/');
	if (!path)
		return (exit_safe_memory_context(), ft_strdup(current));
	i = 0;
	while (path[i])
		i++;
	if (i > 0)
		result = ft_strdup(path[i - 1]);
	else if (path[i])
		result = ft_strdup(path[i]);
	else
		result = ft_strdup("/");
	send_pointer_to_upper_context(result);
	exit_safe_memory_context();
	return (result);
}

char	*get_home_path(t_minishell *data)
{
	char	*path;

	path = (char *)get_env(data->envp, "HOME");
	return (path);
}
// char	*i;
// if (!path)
// {
// 	path = ft_strnstr(data->started_path, "/home/",
// 			ft_strlen(data->started_path));
// 	if (path)
// 	{
// 		i = ft_strchr(path + ft_strlen("/home/"), '/');
// 		if (i)
// 			path = ft_substr(path, 0, i - path);
// 	}
// }
// if (!path)
// 	return (NULL);

char	*get_current_path(t_minishell *data)
{
	char	*path;
	char	current[MAX_PATH_LENGTH];

	getcwd(current, MAX_PATH_LENGTH);
	if (ft_strlen(current) > 0)
		return (ft_strdup(current));
	path = (char *)get_env(data->envp, "PWD");
	if (!path)
		path = (char *)data->started_path;
	return (path);
}

bool	is_path(char *str)
{
	return (ft_strncmp(str, "../", 3) == 0 || ft_strncmp(str, "/", 1) == 0
		|| ft_strncmp(str, "./", 2) == 0);
}

// bool	is_regular_file(const char *path)
// {
// 	struct stat	path_stat;

// 	stat(path, &path_stat);
// 	return (S_ISREG(path_stat.st_mode));
// }

bool	is_directory_file(const char *path)
{
	struct stat	path_stat;

	stat(path, &path_stat);
	return (S_ISDIR(path_stat.st_mode));
}
