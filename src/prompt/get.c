/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <romain@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:27:31 by rguigneb          #+#    #+#             */
/*   Updated: 2025/02/13 20:13:03 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static const char	*get_base_prompt(void)
{
	return (BCYN "$PWD " RESET);
}

const char	*get_prompt(t_minishell *minishell)
{
	char	*prompt;

	prompt = (char *)get_base_prompt();
	if (minishell->exit_code != 0)
		display_arrow(RED);
	else
		display_arrow(GRN);
	prompt = ft_strreplace(prompt, "$PWD", (char *)get_env(minishell->envp,
				"PWD"));
	return ((const char *)prompt);
}
