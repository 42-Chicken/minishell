/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 08:36:57 by rguigneb          #+#    #+#             */
/*   Updated: 2025/03/11 15:07:23 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_H

# define DEFINE_H

# include "minishell.h"

// ---------------------------------
//
// ENV
//
// ---------------------------------

# define ENV_SHLVL "SHLVL"
# define ENV_HOME "HOME"
# define ENV_PATH "PATH"
# define ENV_PWD "PWD"
# define ENV_OLDPWD "OLDPWD"

// ---------------------------------
//
// OTHERS
//
// ---------------------------------

# define HOME_DIRECTORY_REPRESENTATION "~"
# define EXPANDER_EXIT_CODE_PATERN "$?"
# define EXPANDER_PID_PATERN "$$"
# define PID "PIDI"

// ---------------------------------
//
// EXIT CODES
//
// ---------------------------------

# define SIGIN_EXIT_CODE 130

// ---------------------------------
//
// ERRORS
//
// ---------------------------------

# define FAIL_PIPE_MESSAGE "minishell:\
 failed to create a pipe"
# define FAIL_PIPE_EXIT_CODE 1
# define ERROR_CANNOT_ACCESS_WORKING_DIRECTORY "Cannot access \
current working directory !\n"

// ---------------------------------
//
// HEREDOCS
//
// ---------------------------------

# define HEREDOC_WRITTING_FD 4
# define HEREDOC_WARNING "\nminishell\
: warning: here-document at %d delimited by end-of-file (wanted `%s')\n"
# define HEREDOC_PROMPT "> "
# define HEREDOC_TMP_FILE_START_PATH "/tmp/minishell_heredoc_"
# define HEREDOC_ERROR_FILE_CREATION "minishell\
: failed to create heredoc file"

// ---------------------------------
//
// BTREE ERRORS
//
// ---------------------------------

# define ERROR_NO_SUCH_FILE_OR_DIRECTORY "minishell\
: %s: No such file or directory\n"
# define ERROR_NO_SUCH_FILE_OR_DIRECTORY_EXIT_CODE 127
# define ERROR_HEREDOC_FILE_DELETED "minishell\
: %s: Heredoc file has been deleted\n"
# define ERROR_HEREDOC_FILE_PERMISSION_DENIED "minishell\
: %s: Heredoc file doesn't have the right permissions\n"
# define ERROR_PERMISSION_DENIED "minishell\
: %s: Permission denied\n"
# define ERROR_PERMISSION_DENIED_EXIT_CODE 126
# define ERROR_CANNOT_OPEN_FILE "minishell\
: %s: cannot open file\n"
# define ERROR_UNEXPTED_TOKEN_NEW_LINE "minishell\
: syntax error near unexpected token `newline'\n"
# define ERROR_TREE_AND "minishell\
: syntax error: unexpected `&&'\n"
# define ERROR_TREE_OR "minishell\
: syntax error: unexpected `||'\n"
# define ERROR_TREE_PIPE "minishell\
: syntax error: unexpected `|'\n"

// ---------------------------------
//
// BTREE OTHERS
//
// ---------------------------------

# define IS_DIRECTORY_PATH "minishell\
: %s: Is a directory\n"
# define IS_DIRECTORY_PATH_EXIT_CODE 126
# define COMMAND_NOT_FOUND "%s: command not found\n"
# define COMMAND_NOT_FOUND_EXIT_CODE 127
# define ERROR_COMMAND_ARGUMENTS "minishell\
: .: filename argument required\n.: usage: . filename [arguments]\n"
# define ERROR_COMMAND_ARGUMENT_REQUIRED_EXIT_CODE 2

// ---------------------------------
//
// BUILT-IN
//
// ---------------------------------

# define ECHO_BT "echo"
# define CD_BT "cd"
# define EXIT_BT "exit"
# define EXPORT_BT "export"
# define UNSET_BT "unset"
# define PWD_BT "pwd"
# define ENV_BT "env"

#endif
