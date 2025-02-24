/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 19:07:07 by romain            #+#    #+#             */
/*   Updated: 2025/02/24 15:03:16 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "signals.h"
#include <signal.h>

void	close_heredoc(int sig)
{
	g_sig = sig;
	ft_fprintf(STDOUT_FILENO, "\n");
	close(4); // 4 because there is the fd of the file and the dup fd of stdout
}

void	new_line(int sig)
{
	g_sig = sig;
	ft_fprintf(STDOUT_FILENO, "\n", 0);
	ft_fprintf(STDOUT_FILENO, YEL);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	(void)sig;
}

void	switch_to_child_mode(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGTSTP, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	switch_to_heredoc_mode(void)
{
	signal(SIGINT, close_heredoc);
}

void	reset_signals(bool nl)
{
	if (nl)
		signal(SIGINT, new_line);
	else
		signal(SIGINT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	init_signals(t_minishell *data)
{
	// sigset_t set;
	// struct sigaction action;
	// action.sa_flags = SA_RESTART;
	// sigaction(SIGINT, &action, NULL);
	// sigemptyset(&set);
	// // sigaddset(&set, SIGINT);
	// sigaddset(&set, SIGTSTP);
	// sigaddset(&set, SIGQUIT);
	// sigprocmask(SIG_BLOCK, &set, NULL);
	// 	// use sigaction
	// 	sigaction(SIGTSTP, NULL, SIG_IGN);
	reset_signals(true);
	(void)data;
}
