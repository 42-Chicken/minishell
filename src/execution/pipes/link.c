/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 08:30:35 by rguigneb          #+#    #+#             */
/*   Updated: 2025/02/17 12:29:49 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"

void	link_execution_tree_pipes(t_minishell *data)
{
	if (!data || !data->execution_tree)
		return ;
	btree_foreach(&data->execution_tree, execute_redirection_foreach,
		(void *)data);
	btree_foreach(&data->execution_tree, execute_commands_foreach, (void *)data);
}
