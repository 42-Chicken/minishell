/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 09:09:27 by rguigneb          #+#    #+#             */
/*   Updated: 2025/03/05 09:28:45 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	get_dir_files_count(char *path)
{
	size_t	i;
	DIR		*dir;

	i = 0;
	dir = opendir(path);
	while (dir && readdir(dir))
		i++;
	closedir(dir);
	return (i);
}

char	**get_dir_files_into_array(char *path)
{
	char			**tab;
	size_t			len;
	size_t			i;
	DIR				*dir;
	struct dirent	*current;

	i = 0;
	len = get_dir_files_count(path);
	if (len <= 0)
		return (NULL);
	tab = safe_malloc(sizeof(char *) * (len + 1));
	dir = opendir(path);
	if (!dir)
		return (NULL);
	current = readdir(dir);
	while (current)
	{
		tab[i++] = ft_strdup(current->d_name);
		current = readdir(dir);
	}
	tab[len] = NULL;
	closedir(dir);
	return (tab);
}
