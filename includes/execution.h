/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:26:37 by rguigneb          #+#    #+#             */
/*   Updated: 2025/02/17 09:18:20 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H

# define EXECUTION_H

# include "minishell.h"

# define PIPE_NO_VALUE -1

typedef struct s_pipe
{
	int					read;
	int					write;
}						t_pipe;

typedef enum e_command_status
{
	FAILED,
	SUCCESS
}						t_command_status;

typedef enum e_command_errors
{
	NO_ERROR = -1,
	PERMISSION_DENIED,
	NO_SUCH_FILE_OR_DIRECTORY,
	ERROR_OPENING_FILE,
	COMMAND_NOT_FOUND,
}						t_command_errors;

typedef struct s_command
{
	char				**argv;
	char				**envp;
	t_pipe				in_pipe;
	t_pipe				out_pipe;
	t_command_errors	error;
	char				*error_allias;
	struct s_command	*subtree;
	struct s_command	*next[2];
	struct s_command	*prev[2];
}						t_command;

// ---------------------------------
//
// EXECUTION
//
// ---------------------------------
void					execution_pipeline(t_minishell *data);

// ---------------------------------
//
// PIPES
//
// ---------------------------------
t_pipe					get_pipe(void);
void					set_pipe(t_pipe *pipe, t_pipe pipe_value);
void					safe_close(int fd);
void					safe_pipe_close(t_pipe pipe);

#endif
