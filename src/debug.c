/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 09:38:44 by rguigneb          #+#    #+#             */
/*   Updated: 2025/03/13 16:10:02 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "binary_tree.h"
#include "execution.h"
#include "ft_fprintf.h"
#include "minishell.h"

static void	print_commands(t_btree *node, void *content)
{
	t_command	*command;

	command = (t_command *)content;
	ft_fprintf(STDOUT_FILENO,
				"%p > (name : %s pipe : %d | inr : %d inw : %d | outr :\
%d outw : %d) | prev : %p | left : %p | right : %p",
				node,
				command->argv[0],
				command->part_of_pipe,
				command->in_pipe.read,
				command->in_pipe.write,
				command->out_pipe.read,
				command->out_pipe.write,
				node->prev,
				node->left,
				node->right
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
	if (node->type == BTREE_COMMAND_TYPE)
	{
		print_commands(node, (t_command *)node->content);
		ft_fprintf(STDOUT_FILENO, "\n");
		print_recustive(data, node->left, offset + 1);
	}
	if (node->type == BTREE_PIPE_TYPE)
	{
		ft_fprintf(STDOUT_FILENO, "PIPE\n");
		print_recustive(data, node->left, offset + 1);
	}
	if (node->type == BTREE_REDIRECTION_TYPE)
	{
		ft_fprintf(STDOUT_FILENO, "%p > REDIR to %d | file : %s | limiter : %s | error : %d | command : %p | left : %p | right : %p | prev : %p\n",
			node,
			((t_btree_redir_node *)node->content)->fd,
			((t_btree_redir_node *)node->content)->file,
			((t_btree_redir_node *)node->content)->limiter,
			((t_btree_redir_node *)node->content)->error,
			((t_btree_redir_node *)node->content)->command,
			node->left,
			node->right,
			node->prev
		);
		print_recustive(data, node->left, offset + 1);
	}
	else if (node->type == BTREE_OR_TYPE)
	{
		ft_fprintf(STDOUT_FILENO, "OR\n");
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
