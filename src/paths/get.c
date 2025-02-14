/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 10:54:00 by rguigneb          #+#    #+#             */
/*   Updated: 2025/02/14 11:07:45 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_current_path(t_minishell *data)
{
	char	*path;

	path = (char *)get_env(data->envp, "PWD");
	if (!path)
		path = (char *)data->started_path;
	return (path);
}
