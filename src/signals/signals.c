/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 19:07:07 by romain            #+#    #+#             */
/*   Updated: 2025/02/14 11:31:34 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "signals.h"

void	exit_sig(int sig)
{
	ft_fprintf(STDOUT_FILENO, RED);
	rl_on_new_line();
	g_sig = sig;
	(void)sig;
}

void	new_line(int sig)
{
	ft_fprintf(STDOUT_FILENO, "\n");
	ft_fprintf(STDOUT_FILENO, YEL);
	g_sig = sig;
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	(void)sig;
}

void	cancel(int sig)
{
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_sig = sig;
	(void)sig;
}

void	init_signals(t_minishell *data)
{
	signal(SIGINT, new_line);
	signal(SIGTSTP, cancel);
	(void)data;
}
