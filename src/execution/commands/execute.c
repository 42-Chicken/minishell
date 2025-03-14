/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:24:39 by rguigneb          #+#    #+#             */
/*   Updated: 2025/03/13 14:31:49 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "define.h"
#include "execution.h"
#include "minishell.h"

void	close_pipes_until_end(t_btree *cmd_node)
{
	t_btree		*current;
	t_command	*command;

	current = cmd_node;
	while (current)
	{
		if (current->type == BTREE_COMMAND_TYPE && current->content)
		{
			command = (t_command *)current->content;
			if (command->in_pipe.read)
				safe_close(command->in_pipe.read);
			if (command->in_pipe.write)
				safe_close(command->in_pipe.write);
		}
		current = current->left;
	}
}

void	close_and_dup(t_minishell *data, t_command *command)
{
	if (command->in_pipe.write)
		safe_close(command->in_pipe.write);
	if (command->in_pipe.read)
		safe_close(command->out_pipe.read);
	dup2(command->in_pipe.read, STDIN_FILENO);
	dup2(command->out_pipe.write, STDOUT_FILENO);
	update_shlvl(data, (char *)get_env(data->envp, ENV_SHLVL), 1);
	safe_close(command->in_pipe.read);
	safe_close(command->out_pipe.write);
}

static void	exit_with_code(t_btree *cmd_node, t_command *command)
{
	int	code;

	code = 0;
	(void)cmd_node;
	if (command->error == COMMAND_NO_ERROR)
		code = EXIT_SUCCESS;
	if (command->error == COMMAND_NOT_FOUND_ERROR)
		code = COMMAND_NOT_FOUND_EXIT_CODE;
	if (command->error == COMMAND_NO_SUCH_FILE_OR_DIRECTORY_ERROR)
		code = ERROR_NO_SUCH_FILE_OR_DIRECTORY_EXIT_CODE;
	if (command->error == COMMAND_IS_SUCH_FILE_OR_DIRECTORY_ERROR)
		code = IS_DIRECTORY_PATH_EXIT_CODE;
	if (command->error == COMMAND_PERMISSION_DENIED_ERROR)
		code = ERROR_PERMISSION_DENIED_EXIT_CODE;
	if (command->error == COMMAND_ARGUMENT_REQUIRED_ERROR)
		code = ERROR_COMMAND_ARGUMENT_REQUIRED_EXIT_CODE;
	if ((command->out_redir
			&& command->out_redir->error != REDIRECTION_NO_ERROR)
		|| (command->in_redir
			&& command->in_redir->error != REDIRECTION_NO_ERROR))
		code = DEFAULT_ERROR_EXIT_CODE;
	safe_exit(code);
}

static bool	can_execute(t_command *command)
{
	if (command->out_redir && command->out_redir->error != REDIRECTION_NO_ERROR)
		return (false);
	if (command->in_redir && command->in_redir->error != REDIRECTION_NO_ERROR)
		return (false);
	if (command->error != COMMAND_NO_ERROR)
		return (false);
	return (true);
}

void	exec_command(t_minishell *data, t_btree *cmd_node, t_command *command)
{
	pid_t	fork_id;

	set_env(&data->envp, "_", command->argv[0]);
	if (!execute_built_in_command(data, command))
	{
		fork_id = fork();
		if (fork_id == -1)
			safe_exit(EXIT_FAILURE);
		if (fork_id == 0)
		{
			create_safe_memory_context();
			close_and_dup(data, command);
			close_pipes_until_end(cmd_node);
			if (can_execute(command))
				execve(command->argv[0], (char *const *)command->argv,
					(char *const *)data->envp);
			exit_safe_memory_context();
			exit_with_code(cmd_node, command);
		}
	}
}
