/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:26:37 by rguigneb          #+#    #+#             */
/*   Updated: 2025/03/13 12:05:49 by rguigneb         ###   ########.fr       */
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

typedef enum e_quote_type
{
	QUOTE_NONE = -1,
	QUOTE_DOUBLED,
	QUOTE_SIMPLE,
}							t_e_quote_type;

typedef enum e_exec_tree_errors
{
	EXECTREE_ERR_NONE,
	EXECTREE_ERR_UNEXEPTED_PIPE,
	EXECTREE_ERR_UNEXEPTED_OR,
	EXECTREE_ERR_UNEXEPTED_AND,
	EXECTREE_ERR_CANCEL,
	EXECTREE_ERR_UNEXPETED_TOKEN,
}							t_e_exec_tree_errors;

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
	t_e_exec_tree_errors	execution_tree_error;
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
void						check_exec_tree(t_minishell *data);
size_t						char_array_len(char **array);
bool						is_number(char *str);
void						update_shlvl(t_minishell *data, char *str, int d);
void						char_sort_array(char **tab);
bool						ft_str_only_contain(char *str, char *set);
int							ft_max(int a, int b);
bool						is_same_str(char *str1, char *str2);
int							startswith(char *str, char *substr);
int							endswith(char *str, char *substr);
t_e_quote_type				is_in_quote_at(char *str, int index);
char						*ft_custom_strreplace(char *str, char *mask,
								char *value);

#endif
