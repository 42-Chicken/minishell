/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 09:38:44 by rguigneb          #+#    #+#             */
/*   Updated: 2025/02/17 12:02:11 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

// static void	print_recustive(t_minishell *data, t_command *command, int offset)
// {
// 	int i;
// 	if (!data || !command)
// 		return ;
// 	i = -1;
// 	while (++i < offset)
// 		ft_fprintf(STDOUT_FILENO, "	");
// 	ft_fprintf(STDOUT_FILENO,
// 		"name : %s | inr : %d inw : %d | outr : %d outw : %d\n",
// 		command->argv[0],
// 		command->in_pipe.read, command->in_pipe.write,
// 		command->out_pipe.read, command->out_pipe.write
// 	);
// 	if (command->subtree)
// 		print_recustive(data, command->subtree, offset + 1);
// 	if (command->next[SUCCESS] != command->next[FAILED])
// 	{
// 		if (command->next[SUCCESS])
// 			print_recustive(data, command->next[SUCCESS], offset);
// 		if (command->next[FAILED])
// 			print_recustive(data, command->next[FAILED], offset);
// 	}
// 	else
// 		print_recustive(data, command->next[FAILED], offset);
// }

void	print_execution_tree(t_minishell *data)
{
	(void)data;
	// print_recustive(data, data->execution_tree, 0);
}
