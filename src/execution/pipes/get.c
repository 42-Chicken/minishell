/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 08:36:00 by rguigneb          #+#    #+#             */
/*   Updated: 2025/02/17 08:39:58 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"
#include "execution.h"
#include "minishell.h"

t_pipe	get_pipe(void)
{
	t_pipe	in_pipe;

	if (pipe((int *)(&in_pipe)) == -1)
	{
		ft_fprintf(STDERR_FILENO, FAIL_PIPE_MESSAGE);
		safe_exit(FAIL_PIPE_EXIT_CODE);
	}
	return (in_pipe);
}
