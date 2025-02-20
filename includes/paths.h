/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:26:37 by rguigneb          #+#    #+#             */
/*   Updated: 2025/02/20 14:16:03 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PATHS_H

# define PATHS_H

# include "minishell.h"
# include <sys/stat.h>
# include <sys/types.h>

extern int	g_sig;

// ---------------------------------
//
// PATHS
//
// ---------------------------------
char		*get_current_path(t_minishell *data);
char		*get_home_path(t_minishell *data);
char		*cleanup_path(t_minishell *data, char *path1);
void		set_current_path(t_minishell *data, char *new_path);
char		*combine_paths(t_minishell *data, char *path1, char *path2);
char		*get_current_folder_name(void);
bool		is_path(char *str);

bool		is_regular_file(const char *path);
bool		is_directory_file(const char *path);

#endif
