/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 08:54:42 by rguigneb          #+#    #+#             */
/*   Updated: 2025/02/12 12:49:58 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include <stdlib.h>

/******************************************************************************/
const char	*get_env(const char **envp, const char *variable);
void		set_env(const char **envp, const char *variable, char *value);
int			get_env_index(const char **envp, const char *variable);

#endif
