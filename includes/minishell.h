/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <romain@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:26:37 by rguigneb          #+#    #+#             */
/*   Updated: 2025/02/13 20:08:27 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# include "colors.h"
# include "env.h"
# include "ft_fprintf.h"
# include "ft_strings.h"
# include "garbadge.h"
# include "get_next_line.h"
# include "libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_minishell
{
	int			argc;
	char const	**argv;
	char const	**envp;
	int			exit_code;
}				t_minishell;

extern int		g_sig;

// ---------------------------------
//
// SIGNALS
//
// ---------------------------------
void			init_signals(t_minishell *data);

// ---------------------------------
//
// READLINE
//
// ---------------------------------
void			handle_readline(t_minishell *data);

// ---------------------------------
//
// PROMPT
//
// ---------------------------------
const char		*get_prompt(t_minishell *minishell);
void			display_arrow(const char *color);

#endif
