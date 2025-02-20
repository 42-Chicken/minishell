/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 09:24:06 by rguigneb          #+#    #+#             */
/*   Updated: 2025/02/20 11:46:09 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define SHLVL_TO_HIGH_ERROR "bash: warning: \
shell level (%d) too high, resetting to 1\n"

void	update_shlvl(t_minishell *data, char *str, int d)
{
	int	value;

	value = 0;
	if (str && is_number(str))
		value = ft_atoi(str) + d;
	if (value < 0)
		value = 0;
	if (value > 1000 && d == 0)
	{
		ft_fprintf(STDERR_FILENO, SHLVL_TO_HIGH_ERROR, value);
		value = 0;
	}
	set_env(&data->envp, "SHLVL", ft_itoa(value));
}
