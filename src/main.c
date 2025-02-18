/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:25:23 by rguigneb          #+#    #+#             */
/*   Updated: 2025/02/18 10:45:16 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "signals.h"

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
	init_minishell(&data);
	while (!data.stop)
	{
		create_safe_memory_context();
		handle_signals_exit_codes(&data);
		handle_readline(&data);
		exit_safe_memory_context();
	}
	free_all_contexts_garbadge();
	return (data.exit_code);
}
