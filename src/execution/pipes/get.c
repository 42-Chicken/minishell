/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 08:36:00 by rguigneb          #+#    #+#             */
/*   Updated: 2025/03/12 12:42:08 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "define.h"
#include "execution.h"
#include "minishell.h"

t_pipe	get_pipe(void)
{
	t_pipe	in_pipe;

	if (pipe((int *)(&in_pipe)) == -1)
	{
		ft_fprintf(STDERR_FILENO, FAIL_PIPE_MESSAGE);
		return ((t_pipe) {PIPE_NO_VALUE, PIPE_NO_VALUE});
	}
	return (in_pipe);
}
