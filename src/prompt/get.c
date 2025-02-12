/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:27:31 by rguigneb          #+#    #+#             */
/*   Updated: 2025/02/12 16:35:44 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static const char	*get_base_prompt(void)
{
	return ("$COLOR➜  " BCYN "$PWD " RESET);
}

const char	*get_prompt(t_minishell *minishell)
{
	char	*prompt;

	prompt = (char	*)get_base_prompt();
	if (minishell->exit_code != 0)
		prompt = ft_strreplace(prompt, "$COLOR", RED);
	else
		prompt = ft_strreplace(prompt, "$COLOR", GRN);
	prompt = ft_strreplace(prompt, "$PWD", (char *)get_env(minishell->envp, "PWD"));
	return ((const char	*)prompt);
}
