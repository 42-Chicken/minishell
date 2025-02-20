/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:33:52 by rguigneb          #+#    #+#             */
/*   Updated: 2025/02/20 11:44:42 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define EXPORT_INVALID_ID "bash: export: `%s': not a valid identifier\n"

static char	*get_var_value(char *str)
{
	char	*start;

	start = ft_strchr(str, '=');
	if (!start)
		return (NULL);
	start = ft_substr(str, start - str + 1, ft_strlen(str));
	return (start);
}

static char	*get_var_name(char *str)
{
	char	*start;

	start = ft_strchr(str, '=');
	if (!start)
		return (str);
	str = ft_substr(str, 0, start - str);
	return (str);
}

static char	*get_formatted_env_line(char *line)
{
	char	*result;
	char	*value;

	result = get_var_name(line);
	value = get_var_value(line);
	if (!value)
		return (result);
	result = ft_strjoin(result, ft_strdup("=\""));
	result = ft_strjoin(result, value);
	result = ft_strjoin(result, ft_strdup("\""));
	return (result);
}

void	handle_env_update(t_minishell *data, char *str)
{
	char	*name;
	int		index;

	name = get_var_name(str);
	if (!name)
		return ;
	if (!ft_str_only_contain(name, "_"))
	{
		ft_fprintf(STDERR_FILENO, EXPORT_INVALID_ID, name);
		return ;
	}
	str = ft_strdup(str);
	if (ft_strncmp(name, "SHLVL", ft_strlen(name)) == 0)
	{
		update_shlvl(data, get_var_value(str), 0);
		return ;
	}
	send_pointer_to_main_context(str);
	index = get_raw_env_index(data->envp, name);
	if (index != -1)
		data->envp[index] = str;
	else
		add_to_env(&data->envp, str);
}

int	export_command(t_minishell *data, t_command *command)
{
	int	i;

	i = -1;
	char_sort_array((char **)data->envp);
	if (char_array_len(command->argv) <= 1)
	{
		while (data->envp && data->envp[++i])
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
