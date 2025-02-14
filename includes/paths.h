/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:26:37 by rguigneb          #+#    #+#             */
/*   Updated: 2025/02/14 11:07:59 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PATH_H

# define PATH_H

#include "minishell.h"

extern int		g_sig;

// ---------------------------------
//
// PATHS
//
// ---------------------------------
char			*get_current_path(t_minishell *data);
void			set_current_path(t_minishell *data, char *new_path);
char			*combine_paths(t_minishell *data, char *path1, char *path2);

#endif
