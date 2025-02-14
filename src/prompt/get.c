/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:27:31 by rguigneb          #+#    #+#             */
/*   Updated: 2025/02/14 18:49:43 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "paths.h"

static const char	*get_base_prompt(void)
{
	return ("➜  " BCYN "$PWD " RESET);
}

const char	*get_prompt(t_minishell *data)
{
	char	*prompt;

	prompt = (char *)get_base_prompt();
	if (data->exit_code != 0)
		ft_fprintf(STDOUT_FILENO, RED);
	else
		ft_fprintf(STDOUT_FILENO, GRN);
	prompt = ft_strreplace(prompt, "$PWD", get_current_path(data));
	return ((const char *)prompt);
}
