/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   combine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 13:03:06 by rguigneb          #+#    #+#             */
/*   Updated: 2025/02/14 14:26:40 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "paths.h"

// static char	*remove_double_dots(char *path1)
// {
// 	int		i;
// 	char	*part;
// 	char	*last;
// 	char	*sub;
// 	char	*second_sub;

// 	i = 0;
// 	if (!path1)
// 		return (NULL);
// 	while (1)
// 	{
// 		sub = ft_strnstr(path1, "..", ft_strlen(path1));
// 		if (sub)
// 		{
// 			second_sub = ft_strrchr(sub - 1, '/');
// 			if (second_sub)
// 			{
// 				part = ft_substr(path1, 0, second_sub - path1 + 1);
// 				last = ft_substr(path1, sub - path1 + ft_strlen(".."),
// 						ft_strlen(sub + ft_strlen("..")));
// 			}
// 			else
// 			{
// 				part = ft_substr(path1, 0, sub - path1);
// 				last = ft_substr(path1, sub - path1 + ft_strlen(".."),
// 						ft_strlen(sub + ft_strlen("..")));
// 			}
// 			path1 = ft_strjoin(part, last);
// 		}
// 		else
// 			break ;
// 	}
// 	return (path1);
// }

static char	*cleanup_path(t_minishell *data, char *path1)
{
	char	*newstr;

	newstr = ft_strtrim(path1, " \t\n\v\f\r");
	if (newstr == NULL)
		return (ft_strdup(""));
	newstr = ft_strreplace(newstr, "./", NULL);
	newstr = ft_strreplace(newstr, "~", get_home_path(data));
	return (newstr);
}

char	*combine_paths(t_minishell *data, char *path1, char *path2)
{
	int	i;

	// char	**splitted1;
	// char	**splitted2;
	i = 0;
	path1 = cleanup_path(data, path1);
	path2 = cleanup_path(data, path2);
	printf("%s\n", path1);
	// path2 = cleanup_path(data, path2);
	return (cleanup_path(data, path1));
}
