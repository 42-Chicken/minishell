/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:27:31 by rguigneb          #+#    #+#             */
/*   Updated: 2025/02/25 09:47:05 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "define.h"
#include "minishell.h"
#include "paths.h"

// OMZ prompt :
//	return ("➜  " BCYN "$PWD " BBLU "git:(" BRED "testing" BBLU ") 🧪 " RESET);
static const char	*get_base_prompt(void)
{
	return ("⦿︎  $SHLVL $CODE " BCYN "$PWD " BBLU "$GIT"
			"🧪 " RESET);
}

// TO chnage with the expander
const char	*get_prompt(t_minishell *data)
{
	char	*prompt;
	char	*home;

	create_safe_memory_context();
	home = get_home_path(data);
	prompt = (char *)get_base_prompt();
	if (data->exit_code != 0)
		ft_fprintf(STDOUT_FILENO, RED);
	else
		ft_fprintf(STDOUT_FILENO, GRN);
	if (home && ft_strncmp(get_current_path(data), home, MAX_PATH_LENGTH) == 0)
		prompt = ft_strreplace(prompt, "$PWD", HOME_DIRECTORY_REPRESENTATION);
	else
		prompt = ft_strreplace(prompt, "$PWD", get_current_folder_name());
	if (access(".git", F_OK) != -1)
		prompt = ft_strreplace(prompt, "$GIT",
				"git:(" BRED "testing" BBLU ") ");
	else
		prompt = ft_strreplace(prompt, "$GIT", "");
	prompt = ft_strreplace(prompt, "$SHLVL", (char *)get_env(data->envp,
				ENV_SHLVL));
	prompt = ft_strreplace(prompt, "$CODE", ft_itoa(data->exit_code));
	send_pointer_to_upper_context(prompt);
	exit_safe_memory_context();
	return ((const char *)prompt);
}
