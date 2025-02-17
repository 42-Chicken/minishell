/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:26:37 by rguigneb          #+#    #+#             */
/*   Updated: 2025/02/17 12:03:31 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H

# define EXECUTION_H

# define PIPE_NO_VALUE -1

# include "libft.h"
# include "garbadge.h"

typedef struct s_minishell	t_minishell;

typedef struct s_pipe
{
	int						read;
	int						write;
}							t_pipe;

typedef enum e_command_status
{
	FAILED,
	SUCCESS
}							t_command_status;

typedef enum e_command_errors
{
	NO_ERROR = -1,
	PERMISSION_DENIED,
	NO_SUCH_FILE_OR_DIRECTORY,
	ERROR_OPENING_FILE,
	COMMAND_NOT_FOUND,
}							t_command_errors;

typedef enum e_redirection_types

{
	REDIRECTION_IN_TYPE,
	REDIRECTION_OUT_TYPE
}							t_redirection_types;

typedef struct s_command
{
	char					**argv;
	char					**envp;
	t_pipe					in_pipe;
	t_pipe					out_pipe;
	t_command_errors		error;
	char					*error_allias;
}							t_command;

typedef struct s_btree_command_node
{
	t_list					*commands;
	t_pipe					in_pipe;
	t_pipe					out_pipe;
}							t_btree_command_node;

typedef struct s_btree_redirection_node
{
	int						fd;
	char					*file;
	t_redirection_types		type;
}							t_btree_redirection_node;

// ---------------------------------
//
// EXECUTION
//
// ---------------------------------
void						execution_pipeline(t_minishell *data);

// ---------------------------------
//
// PIPES
//
// ---------------------------------
t_pipe						get_pipe(void);
void						set_pipe(t_pipe *pipe, t_pipe pipe_value);
void						safe_close(int fd);
void						safe_pipe_close(t_pipe pipe);
void						link_execution_tree_pipes(t_minishell *data);

// ---------------------------------
//
// DEBUG
//
// ---------------------------------
void						print_execution_tree(t_minishell *data);

#endif
