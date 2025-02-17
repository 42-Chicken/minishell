/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 09:38:44 by rguigneb          #+#    #+#             */
/*   Updated: 2025/02/17 14:18:38 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"
#include "execution.h"
#include "binary_tree.h"
#include "ft_fprintf.h"

static void print_commands(void *content)
{
	t_command *command;

	command = (t_command *)content;
	ft_fprintf(STDOUT_FILENO,
		"name : %s | inr : %d inw : %d | outr : %d outw : %d\n",
		command->argv[0],
		command->in_pipe.read, command->in_pipe.write,
		command->out_pipe.read, command->out_pipe.write
	);
}

static void	print_recustive(t_minishell *data, t_btree *node, int offset)
{
	t_btree_command_node	*cmds_node;
	int i;

	if (!data || !node)
		return ;
	i = -1;
	cmds_node = NULL;
	while (++i < offset)
		ft_fprintf(STDOUT_FILENO, "	");
	if (node->type == BTREE_COMMANDS_TYPE)
	{
		i = -1;
		while (++i < offset)
			ft_fprintf(STDOUT_FILENO, "	");
		cmds_node = (t_btree_command_node *)node->content;
		ft_lstiter(cmds_node->commands[0], print_commands);
		i = -1;
		while (++i < offset * 2)
			ft_fprintf(STDOUT_FILENO, "	");
		ft_lstiter(cmds_node->commands[1], print_commands);
	}
	if (node->type == BTREE_OR_TYPE)
	{
		ft_fprintf(STDOUT_FILENO, "OR\n");
	}
	if (node->type == BTREE_AND_TYPE)
	{
		ft_fprintf(STDOUT_FILENO, "AND\n");
	}
	if (node->type == BTREE_REDIRECTION_TYPE)
	{
		ft_fprintf(STDOUT_FILENO, "REDIRECT\n");
	}
	if (node->left == node->right)
		print_recustive(data, node->left, offset + 1);
	else
	{
		print_recustive(data, node->left, offset + 1);
		print_recustive(data, node->right, offset + 1);
	}
}

void	print_execution_tree(t_minishell *data)
{
	print_recustive(data, data->execution_tree, 0);
}
