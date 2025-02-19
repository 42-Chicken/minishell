/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 09:38:44 by rguigneb          #+#    #+#             */
/*   Updated: 2025/02/19 12:59:01 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "binary_tree.h"
#include "execution.h"
#include "ft_fprintf.h"
#include "minishell.h"

static void	print_commands(void *content)
{
	t_command	*command;

	command = (t_command *)content;
	ft_fprintf(STDOUT_FILENO,
				"(name : %s pipe : %d | inr : %d inw : %d | outr : %d outw : %d) ",
				command->argv[0],
				command->part_of_pipe,
				command->in_pipe.read,
				command->in_pipe.write,
				command->out_pipe.read,
				command->out_pipe.write
	);
}

static void	print_recustive(t_minishell *data, t_btree *node, int offset)
{
	int	i;

	if (!data || !node)
		return ;
	i = -1;
	while (++i < offset)
		ft_fprintf(STDOUT_FILENO, "	");
	if (node->type == BTREE_COMMANDS_CONTENT_TYPE)
	{
		ft_lstiter((t_list *)node->content, print_commands);
		ft_fprintf(STDOUT_FILENO, "\n");
	}
	else if (node->type == BTREE_OR_TYPE)
	{
		ft_fprintf(STDOUT_FILENO, "OR\n");
		print_recustive(data, node->left, offset + 1);
		print_recustive(data, node->right, offset + 1);
	}
	else if (node->type == BTREE_COMMANDS_TYPE)
	{
		ft_fprintf(STDOUT_FILENO, "COMMANDS\n");
		print_recustive(data, node->left, offset + 1);
		print_recustive(data, node->right, offset + 1);
	}
	else if (node->type == BTREE_AND_TYPE)
	{
		ft_fprintf(STDOUT_FILENO, "AND\n");
		print_recustive(data, node->left, offset + 1);
		print_recustive(data, node->right, offset + 1);
	}
}

void	print_execution_tree(t_minishell *data)
{
	print_recustive(data, data->execution_tree, 0);
}
