/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_codes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 10:26:38 by rguigneb          #+#    #+#             */
/*   Updated: 2025/02/25 09:21:34 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "signals.h"
#include "define.h"
#include <signal.h>

void	handle_signals_exit_codes(t_minishell *data)
{
	if (g_sig == SIGINT)
	{
		data->exit_code = SIGIN_EXIT_CODE;
		g_sig = 0;
	}
}
