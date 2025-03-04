/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 08:54:42 by rguigneb          #+#    #+#             */
/*   Updated: 2025/02/26 09:53:26 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include <stdbool.h>
# include <stdlib.h>

/******************************************************************************/
const char	*get_env(const char **envp, const char *variable);
int			get_env_length(const char **envp);
void		set_env(const char ***envp, const char *variable, char *value);
int			get_env_index(const char **envp, const char *variable);
void		add_to_env(const char ***envp, char *line);
int			get_raw_env_index(const char **envp, const char *variable);
void		remove_from_env(const char ***envp, const char *variable);
void		remove_from_env_index(const char ***envp, int index);

char		*get_var_value(char *str);
int			custom_get_var_env_index(const char **envp, const char *variable);
char		*get_var_name(char *str);
char		*get_formatted_env_line(char *line);

#endif
