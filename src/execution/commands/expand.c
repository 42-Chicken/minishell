/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:44:01 by rguigneb          #+#    #+#             */
/*   Updated: 2025/03/13 15:12:33 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// argv[i] = expand(data, argv[i]);
// static void	expand_argv(t_minishell *data, char **argv)
// {
// 	int	i;

// 	i = -1;
// 	while (argv && argv[++i])
// 	{
// 		(void)data;
// 	}
// }

// if (node->type == BTREE_COMMAND_TYPE)
// {
// 	current = (t_command *)node->content;
// 	// expand_argv(data, current->argv);
// }
void	expand_commands_args(t_minishell *data, t_btree *node)
{
	while (node)
	{
		if (node->type == BTREE_REDIRECTION_TYPE)
		{
			if (((t_btree_redir_node *)node->content)->type != \
						REDIRECTION_HERE_DOC_TYPE)
				((t_btree_redir_node *)node->content)->file = expand(data,
						((t_btree_redir_node *)node->content)->file);
		}
		node = node->left;
	}
}
