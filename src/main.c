/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:25:23 by rguigneb          #+#    #+#             */
/*   Updated: 2025/02/12 12:52:24 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char const **argv, const char **envp)
{
	(void)argc;
	(void)argv;
	ft_fprintf(STDOUT_FILENO, RED "minishel started !\n" RESET);
	free_all_contexts_garbadge();
	return (EXIT_SUCCESS);
}
