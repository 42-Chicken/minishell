/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:26:37 by rguigneb          #+#    #+#             */
/*   Updated: 2025/02/18 15:23:31 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# include "binary_tree.h"
# include "colors.h"
# include "env.h"
# include "ft_fprintf.h"
# include "ft_strings.h"
# include "garbage.h"
# include "get_next_line.h"
# include "libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define MAX_PATH_LENGTH 4095

typedef struct s_command	t_command;

typedef struct s_minishell
{
	int						argc;
	char const				**argv;
	char const				**envp;
	char const				started_path[MAX_PATH_LENGTH];
	t_btree					*execution_tree;
	int						exit_code;
	bool					stop;
}							t_minishell;

// ---------------------------------
//
// INITIALISATION
//
// ---------------------------------
void						init_minishell(t_minishell *data);

// ---------------------------------
//
// READLINE
//
// ---------------------------------
void						handle_readline(t_minishell *data);

// ---------------------------------
//
// PROMPT
//
// ---------------------------------
const char					*get_prompt(t_minishell *minishell);

// ---------------------------------
//
// UTILS
//
// ---------------------------------
size_t						char_array_len(char **array);

#endif
