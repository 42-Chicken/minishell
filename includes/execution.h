/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:26:37 by rguigneb          #+#    #+#             */
/*   Updated: 2025/02/25 09:12:13 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H

# define EXECUTION_H

# define PIPE_NO_VALUE -1

# include "garbage.h"
# include "libft.h"
# include <sys/wait.h>

typedef struct s_btree		t_btree;
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
	COMMAND_NO_ERROR = -1,
	COMMAND_PERMISSION_DENIED_ERROR,
	COMMAND_IS_SUCH_FILE_OR_DIRECTORY_ERROR = 126,
	COMMAND_NO_SUCH_FILE_OR_DIRECTORY_ERROR = 127,
	COMMAND_NOT_FOUND_ERROR,
	COMMAND_ARGUMENT_REQUIRED_ERROR,
}							t_command_errors;

typedef enum e_redirection_errors
{
	REDIRECTION_NO_ERROR = -1,
	REDIRECTION_NO_SUCH_FILE_OR_DIRECTORY,
	REDIRECTION_HERE_DOC_NO_SUCH_FILE_OR_DIRECTORY,
	REDIRECTION_HERE_DOC_PERMISSION_DENIED,
	REDIRECTION_ERROR_OPENING_FILE,
	REDIRECTION_PERMISSION_DENIED,
}							t_redirection_errors;

typedef enum e_redirection_types
{
	REDIRECTION_IN_TYPE,
	REDIRECTION_HERE_DOC_TYPE,
	REDIRECTION_OUT_TYPE
}							t_redirection_types;

typedef struct s_command
{
	char					**argv;
	char					**envp;
	bool					part_of_pipe;
	t_pipe					in_pipe;
	t_pipe					out_pipe;
	t_command_errors		error;
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
	char					*limiter;
	bool					doubled;
	t_redirection_errors	error;
	t_redirection_types		type;
}							t_btree_redir_node;

// ---------------------------------
//
// ERRORS
//
// ---------------------------------
void						checks_redirections_errors(t_minishell *data);
void						print_tree_errors(t_minishell *data);

// ---------------------------------
//
// BUILT_IN
//
// ---------------------------------
bool						is_built_in_command(t_command *command);
bool						execute_built_in_command(t_minishell *data,
								t_command *command);
int							cd_command(t_minishell *data, t_command *command);
int							echo_command(t_minishell *data, t_command *command);
int							pwd_command(t_minishell *data, t_command *command);
int							export_command(t_minishell *data,
								t_command *command);
int							unset_command(t_minishell *data,
								t_command *command);
int							env_command(t_minishell *data, t_command *command);
int							exit_command(t_minishell *data, t_command *command);

// ---------------------------------
//
// EXECUTION
//
// ---------------------------------

void						handle_commands(t_minishell *data, t_btree *node);
void						process_and_logic(t_minishell *data, t_btree *node);
void						process_or_logic(t_minishell *data, t_btree *node);
void						recusrive_execute_binary_tree(t_minishell *data,
								t_btree *node);
void						save_heredocs_tmp_files(t_minishell *data);
void						delete_heredocs_tmp_files(t_minishell *data);
void						bind_redirections_to_fds(t_minishell *data);
void						bind_commands_to_executable(t_minishell *data);
void						execution_pipeline(t_minishell *data);
void						execute_binary_tree(t_minishell *data);
void						wait_all_commands_executions(t_minishell *data);
void						exec_command(t_minishell *data, t_btree *cmd_node,
								t_command *command);

// ---------------------------------
//
// PIPES
//
// ---------------------------------
t_pipe						get_pipe(void);
void						set_pipe(t_pipe *pipe, t_pipe pipe_value);
void						safe_close(int fd);
void						safe_pipe_close(t_pipe pipe);
void						link_commands_pipes(t_btree *lst);
void						link_commands_redirections(t_btree *redir_node);

// ---------------------------------
//
// DEBUG
//
// ---------------------------------
void						print_execution_tree(t_minishell *data);

#endif
