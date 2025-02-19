/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_close.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:05:42 by rguigneb          #+#    #+#             */
/*   Updated: 2025/02/19 11:05:47 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	safe_close(int fd)
{
	if (fd && fd != -1 && fd != STDERR_FILENO && fd != STDOUT_FILENO)
		close(fd);
}

void	safe_pipe_close(t_pipe pipe)
{
	safe_close(pipe.read);
	safe_close(pipe.write);
}
