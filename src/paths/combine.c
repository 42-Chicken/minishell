/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   combine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 13:03:06 by rguigneb          #+#    #+#             */
/*   Updated: 2025/02/17 08:15:23 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "paths.h"

static void	remove_dots(char **splitted)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (splitted[++i])
	{
		if (ft_strncmp(splitted[i], ".", ft_strlen(splitted[i])) == 0)
			splitted[i] = "";
		else if (ft_strncmp(splitted[i], "..", ft_strlen(splitted[i])) == 0)
		{
			splitted[i] = "";
			count++;
		}
	}
	while (--i >= 0)
	{
		if (ft_strlen(splitted[i]) <= 0)
			continue ;
		if (count > 0)
		{
			count--;
			splitted[i] = "";
		}
	}
}

static char	*remove_double_dots(char *path1)
{
	int		i;
	int		d;
	char	**splitted;

	i = -1;
	d = 0;
	if (!path1)
		return ("/");
	if (ft_strlen(path1) == 0)
		return (path1);
	splitted = ft_split(path1, '/');
	remove_dots(splitted);
	path1 = ft_strdup("");
	i = -1;
	while (splitted[++i])
	{
		if (ft_strlen(splitted[i]) > 0)
		{
			path1 = ft_strjoin(path1, "/");
			path1 = ft_strjoin(path1, splitted[i]);
		}
	}
	if (ft_strlen(path1) <= 0)
		path1 = ft_strdup("/");
	return (path1);
}

char	*cleanup_path(t_minishell *data, char *path)
{
	char	*newstr;

	if (!path || ft_strlen(path) <= 0)
		return (ft_strdup(""));
	newstr = ft_strtrim(path, " \t\n\v\f\r");
	if (newstr == NULL)
		return (ft_strdup(""));
	newstr = ft_strreplace(newstr, "~", get_home_path(data));
	return (remove_double_dots(newstr));
}

char	*combine_paths(t_minishell *data, char *path1, char *path2)
{
	path1 = cleanup_path(data, path1);
	path2 = cleanup_path(data, path2);
	return (ft_strjoin(path1, path2));
}
