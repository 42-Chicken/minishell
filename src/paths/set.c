/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 12:08:43 by rguigneb          #+#    #+#             */
/*   Updated: 2025/02/25 09:16:42 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "paths.h"
#include "define.h"

void	set_current_path(t_minishell *data, char *new_path)
{
	set_env(&data->envp, ENV_PWD, new_path);
}
