/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:27:31 by rguigneb          #+#    #+#             */
/*   Updated: 2025/02/20 10:00:45 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "paths.h"

static const char	*get_base_prompt(void)
{
	// OMZ prompt :
	//	return ("➜  " BCYN "$PWD " BBLU "git:(" BRED "testing" BBLU ") 🧪 " RESET);
	return ("⦿︎  $SHLVL " BCYN "$PWD " BBLU "$GIT" "🧪 " RESET);
}

const char	*get_prompt(t_minishell *data)
{
	char	*prompt;

	create_safe_memory_context();
	prompt = (char *)get_base_prompt();
	if (data->exit_code != 0)
		ft_fprintf(STDOUT_FILENO, RED);
	else
		ft_fprintf(STDOUT_FILENO, GRN);
	if (ft_strncmp(get_current_path(data), get_home_path(data), MAX_PATH_LENGTH) != 0)
		prompt = ft_strreplace(prompt, "$PWD", get_current_folder_name());
	else
		prompt = ft_strreplace(prompt, "$PWD", "~");
	if (access(".git", F_OK) != -1)
		prompt = ft_strreplace(prompt, "$GIT", "git:(" BRED "testing" BBLU ") ");
	else
		prompt = ft_strreplace(prompt, "$GIT", "");
	prompt = ft_strreplace(prompt, "$SHLVL", (char *)get_env(data->envp, "SHLVL"));
	send_pointer_to_upper_context(prompt);
	exit_safe_memory_context();
	return ((const char *)prompt);
}
