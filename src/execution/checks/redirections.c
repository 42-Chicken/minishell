/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 12:50:51 by rguigneb          #+#    #+#             */
/*   Updated: 2025/02/20 13:15:49 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"

static void	check_redirection(t_btree *node)
{
	t_btree_redirection_node	*redirection;

	redirection = (t_btree_redirection_node *)node->content;
	if (access(redirection->file, F_OK) == -1)
		redirection->error = REDIRECTION_NO_SUCH_FILE_OR_DIRECTORY;
	else if (redirection->type == REDIRECTION_IN_TYPE
		&& access(redirection->file, R_OK) == -1)
		redirection->error = REDIRECTION_PERMISSION_DENIED;
	else if (redirection->type == REDIRECTION_OUT_TYPE
		&& access(redirection->file, W_OK) == -1)
		redirection->error = REDIRECTION_PERMISSION_DENIED;
}

static void	recursive_redirections_errors(t_btree *node)
{
	if (!node)
		return ;
	if (node->type == BTREE_REDIRECTION_TYPE)
		check_redirection(node);
	recursive_redirections_errors(node->left);
	recursive_redirections_errors(node->right);
}

void	checks_redirections_errors(t_minishell *data)
{
	recursive_redirections_errors(data->execution_tree);
}
