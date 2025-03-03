/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:26:37 by rguigneb          #+#    #+#             */
/*   Updated: 2025/03/03 10:14:52 by rguigneb         ###   ########.fr       */
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
# include <dirent.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define MAX_PATH_LENGTH 4095
# define SPACES " \t\n\v\f\r"
# define KEYWORDS "|&<>"

typedef struct s_command	t_command;

typedef struct s_minishell
{
	int						argc;
	char const				**argv;
	char const				**envp;
	int						line_count;
	char					*current_line;
	char const				started_path[MAX_PATH_LENGTH];
	t_btree					*execution_tree;
	unsigned char			exit_code;
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
// EXPANDER
//
// ---------------------------------
char						*expand(t_minishell *data, char *str);
char						*handle_wildcard(t_minishell *data, char *str);
size_t						get_dir_files_count(char *path);
char						**get_dir_files_into_array(char *path);

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
bool						is_number(char *str);
void						update_shlvl(t_minishell *data, char *str, int d);
void						char_sort_array(char **tab);
bool						ft_str_only_contain(char *str, char *set);
int							ft_max(int a, int b);
bool						is_same_str(char *str1, char *str2);
int							startswith(char *str, char *substr);
int							endswith(char *str, char *substr);

#endif
