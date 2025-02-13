/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <romain@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:25:23 by rguigneb          #+#    #+#             */
/*   Updated: 2025/02/13 19:57:40 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sig = 0;

int	main(int argc, char const **argv, const char **envp)
{
	t_minishell	data;

	ft_bzero(&data, sizeof(t_minishell));
	data.argc = argc;
	data.argv = argv;
	data.envp = envp;
	if (!isatty(0))
		return (EXIT_FAILURE);
	init_signals(&data);
	while (1)
	{
		create_safe_memory_context();
		handle_readline(&data);
		exit_safe_memory_context();
	}
	free_all_contexts_garbadge();
	return (EXIT_SUCCESS);
}
