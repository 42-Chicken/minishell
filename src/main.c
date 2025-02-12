/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:25:23 by rguigneb          #+#    #+#             */
/*   Updated: 2025/02/12 16:23:32 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char const **argv, const char **envp)
{
	t_minishell	data;

	data.argc = argc;
	data.argv = argv;
	data.envp = (char **)envp;
	while (1)
	{
		create_safe_memory_context();
		readline((const char *)ft_strreplace(PROMPT, "$PWD",
				(char *)get_env(envp, "PWD")));
		exit_safe_memory_context();
	}
	free_all_contexts_garbadge();
	return (EXIT_SUCCESS);
}
