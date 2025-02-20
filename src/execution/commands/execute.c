/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:24:39 by rguigneb          #+#    #+#             */
/*   Updated: 2025/02/20 11:45:35 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static char	*get_full_path(const char *path)
{
	return (ft_strjoin(path, "/"));
}

static void	execute_for_every_paths(t_command *command)
{
	char	*command_name;
	int		i;
	char	*path;
	char	**path_env;

	i = 0;
	execve(command->argv[0], (char *const *)command->argv,
		(char *const *)command->envp);
	path = (char *)get_env((char const **)command->envp, "PATH");
	if (!path)
		return ;
	path_env = ft_split(path, ':');
	while (path_env && path_env[i])
	{
		command_name = ft_strjoin(get_full_path(path_env[i++]),
				command->argv[0]);
		execve(command_name, (char *const *)command->argv,
			(char *const *)command->envp);
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
	update_shlvl(data, (char *)get_env(data->envp, "SHLVL"), 1);
	command->envp = (char **)data->envp;
	safe_close(command->in_pipe.read);
	safe_close(command->out_pipe.write);
}

void	exec_command(t_minishell *data, t_btree *cmd_node, t_command *command)
{
	pid_t	fork_id;

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
			if (command->error == COMMAND_NO_ERROR)
				execute_for_every_paths(command);
			exit_safe_memory_context();
			safe_exit(EXIT_FAILURE);
		}
	}
	if (command->in_pipe.write)
		safe_close(command->in_pipe.write);
	if (command->in_pipe.read)
		safe_close(command->in_pipe.read);
	if (command->out_pipe.write)
		safe_close(command->out_pipe.write);
}
