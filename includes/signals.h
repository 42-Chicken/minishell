/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:26:37 by rguigneb          #+#    #+#             */
/*   Updated: 2025/02/25 08:30:22 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H

# define SIGNALS_H

# include "minishell.h"
# include <signal.h>

extern int	g_sig;

// ---------------------------------
//
// SIGNALS
//
// ---------------------------------
void		handle_signals_exit_codes(t_minishell *data);

void		switch_to_heredoc_mode(void);
void		switch_to_child_mode(void);
void		reset_signals(bool nl);

#endif
