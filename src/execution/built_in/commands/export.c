/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:33:52 by rguigneb          #+#    #+#             */
/*   Updated: 2025/02/20 10:48:15 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_formatted_env_line(char *line)
{
	char	*start;
	char	*result;

	start = ft_strchr(line, '=');
	if (!start)
		return (line);
	result = ft_substr(line, 0, start - line);
	result = ft_strjoin(result, ft_strdup("=\""));
	start = ft_substr(line, start - line + 1, ft_strlen(line));
	if (!start)
		return (line);
	result = ft_strjoin(result, start);
	result = ft_strjoin(result, ft_strdup("\""));
	return (result);
}

static char	*get_var_name(char *str)
{
	char	*start;
	char	*result;

	start = ft_strchr(str, '=');
	if (!start)
		return (str);
	result = ft_substr(str, 0, start - str);
	return (result);
}

static char	**get_sorted_tab(char **tab)
{
	int		i;
	int		y;
	int		len;
	char	*temp;

	if (!tab)
		return (NULL);
	i = -1;
	len = char_array_len(tab);
	while (++i < len && tab[i])
	{
		y = -1;
		while (++y < len && tab[y])
		{
			if (ft_strncmp(tab[i], tab[y], ft_strlen(tab[i])) < 0)
			{
				temp = tab[i];
				tab[i] = tab[y];
				tab[y] = temp;
			}
		}
	}
	return (tab);
}

void	handle_env_update(t_minishell *data, char *str)
{
	char	*name;
	int		index;

	name = get_var_name(str);
	if (!name)
		return ;
	index = get_env_index(data->envp, name);
	printf("current : %d\n", index);
	if (index != -1)
		data->envp[index] = str;
	else
	{
		ft_strdup(str);
		// send_pointer_to_upper_context(str);
		add_to_env(&data->envp, str);
	}
}

int	export_command(t_minishell *data, t_command *command)
{
	int		i;
	char	**sorted_env;

	i = -1;
	sorted_env = get_sorted_tab((char **)data->envp);
	if (char_array_len(command->argv) <= 1)
	{
		while (sorted_env && sorted_env[++i])
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
