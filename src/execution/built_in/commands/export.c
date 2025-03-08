/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:33:52 by rguigneb          #+#    #+#             */
/*   Updated: 2025/03/08 14:43:00 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "define.h"
#include "env.h"
#include "minishell.h"

#define EXPORT_INVALID_ID "minishell\
: export: `%s': not a valid identifier\n"

static bool	handle_addition(t_minishell *data, char *name, char *str)
{
	char	*value;
	char	*old_value;
	char	*joined;

	value = get_var_value(str);
	if (!value)
		value = ft_strdup("");
	value = ft_strreplace(value, "\"", "");
	old_value = (char *)get_env(data->envp, name);
	if (!old_value)
		old_value = ft_strdup("");
	joined = ft_strjoin(old_value, value);
	if (joined)
		set_env(&data->envp, name, joined);
	return (true);
}

static bool	handle_env_update(t_minishell *data, char *str)
{
	char	*name;
	int		index;

	name = get_var_name(str);
	if (!name)
		return (false);
	if (!ft_str_only_contain(name, "_"))
		return (ft_fprintf(STDERR_FILENO, EXPORT_INVALID_ID, name), false);
	if (ft_strlen(str) >= 3 && ft_strncmp(str + ft_strlen(name), "+=", 2) == 0)
		return (handle_addition(data, name, str));
	str = ft_strdup(str);
	str = ft_strreplace(str, "\"", "");
	if (ft_strncmp(name, ENV_SHLVL, ft_strlen(name)) == 0)
		return (update_shlvl(data, get_var_value(str), 0), false);
	send_pointer_to_main_context(str);
	index = custom_get_var_env_index(data->envp, name);
	printf("%s %d\n", name, index);
	if (index != -1)
	{
		if (ft_strlen(str + ft_strlen(name)) > 0)
			data->envp[index] = str;
	}
	else
		add_to_env(&data->envp, str);
	return (true);
}

int	export_command(t_minishell *data, t_command *command)
{
	int	i;

	i = -1;
	char_sort_array((char **)data->envp);
	if (char_array_len(command->argv) <= 1)
	{
		while (data->envp && data->envp[++i]
			&& startswith((char *)data->envp[i], "_=") == 0)
			ft_fprintf(command->out_pipe.write, "declare -x %s\n",
				get_formatted_env_line((char *)data->envp[i]));
	}
	else
	{
		i++;
		while (command->argv[++i])
			handle_env_update(data, command->argv[i]);
	}
	return (EXIT_SUCCESS);
}
