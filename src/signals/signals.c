/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 19:07:07 by romain            #+#    #+#             */
/*   Updated: 2025/03/13 11:42:39 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "define.h"
#include "minishell.h"
#include "signals.h"
#include <signal.h>

// 4 because there is the fd of the file and the dup fd of stdout
void	close_heredoc(int sig)
{
	g_sig = sig;
	ft_fprintf(STDOUT_FILENO, "\n");
	rl_replace_line("", 0);
	rl_redisplay();
	close(HEREDOC_WRITTING_FD);
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

// signal(SIGPIPE, SIG_IGN);
void	reset_signals(bool nl)
{
	if (nl)
		signal(SIGINT, new_line);
	else
		signal(SIGINT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}
