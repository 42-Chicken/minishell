/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 12:50:51 by rguigneb          #+#    #+#             */
/*   Updated: 2025/02/20 17:28:10 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"

static void	check_redirection(t_btree **head, t_btree *node)
{
	t_btree_redir_node	*redirection;

	(void)head;
	redirection = (t_btree_redir_node *)node->content;
	if (access(redirection->file, F_OK) == -1)
		redirection->error = REDIRECTION_NO_SUCH_FILE_OR_DIRECTORY;
	else if (redirection->type == REDIRECTION_IN_TYPE
		&& access(redirection->file, R_OK) == -1)
		redirection->error = REDIRECTION_PERMISSION_DENIED;
	else if (redirection->type == REDIRECTION_OUT_TYPE
		&& access(redirection->file, W_OK) == -1)
		redirection->error = REDIRECTION_PERMISSION_DENIED;
}

void	checks_redirections_errors(t_minishell *data)
{
	btree_type_foreach(&data->execution_tree, BTREE_REDIRECTION_TYPE,
		check_redirection);
}
