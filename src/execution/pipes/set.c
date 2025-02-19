/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 08:36:00 by rguigneb          #+#    #+#             */
/*   Updated: 2025/02/17 09:55:59 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"
#include "execution.h"
#include "minishell.h"

void	set_pipe(t_pipe	*pipe, t_pipe pipe_value)
{
	if (!pipe)
		return ;
	if (pipe_value.read != PIPE_NO_VALUE)
		pipe->read = pipe_value.read;
	if (pipe_value.write != PIPE_NO_VALUE)
		pipe->write = pipe_value.write;
}
