/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:24:39 by rguigneb          #+#    #+#             */
/*   Updated: 2025/02/19 14:55:34 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"

void	close_pipes_until_end(t_list *cmds_lst, t_command *target)
{
	t_list		*current;
	t_command	*command;

	current = cmds_lst;
	while (current && current->content != target)
	{
		current = current->next;
	}
	if (current)
		current = current->next;
	while (current && current->content)
	{
		command = (t_command *)current->content;
		if (command->in_pipe.read)
			safe_close(command->in_pipe.read);
		if (command->in_pipe.write)
			safe_close(command->in_pipe.write);
		current = current->next;
	}
	// if (data->in_file_fd != -1)
	// 	safe_close(data->in_file_fd);
	// if (data->out_file_fd != -1)
	// 	safe_close(data->out_file_fd);
}

static char	*get_full_path(const char *path)
{
	return (ft_strjoin(path, "/"));
}

static void	execute_for_every_paths(t_command *command)
{
	char	*command_name;
	int		i;
	char	**path_env;

	i = 0;
	execve(command->argv[0], (char *const *)command->argv,
		(char *const *)command->envp);
	path_env = ft_split(get_env((const char **)command->envp, "PATH"), ':');
	while (path_env && path_env[i])
	{
		command_name = ft_strjoin(get_full_path(path_env[i++]),
				command->argv[0]);
		execve(command_name, (char *const *)command->argv,
			(char *const *)command->envp);
	}
}

void	close_and_dup(t_command *command)
{
	if (command->in_pipe.write)
		safe_close(command->in_pipe.write);
	if (command->in_pipe.read)
		safe_close(command->out_pipe.read);
	dup2(command->in_pipe.read, STDIN_FILENO);
	dup2(command->out_pipe.write, STDOUT_FILENO);
	safe_close(command->in_pipe.read);
	safe_close(command->out_pipe.write);
}

void	exec_command(t_minishell *data, t_list *cmds_lst, t_command *command)
{
	pid_t	fork_id;

	(void)data;
	if (!execute_built_in_command(data, cmds_lst, command))
	{
		fork_id = fork();
		if (fork_id == -1)
			safe_exit(EXIT_FAILURE);
		if (fork_id == 0)
		{
			(void)cmds_lst;
			create_safe_memory_context();
			close_and_dup(command);
			close_pipes_until_end(cmds_lst, command);
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

void	execute_commands_list(t_minishell *data, t_list *lst)
{
	t_list		*current;
	t_command	*command;

	current = lst;
	// print_execution_tree(data);
	(void)current;
	(void)data;
	while (current)
	{
		command = (t_command *)current->content;
		exec_command(data, lst, command);
		current = current->next;
	}
}
