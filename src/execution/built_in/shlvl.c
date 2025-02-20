/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 09:24:06 by rguigneb          #+#    #+#             */
/*   Updated: 2025/02/20 10:39:14 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define SHLVL_TO_HIGH_ERROR "bash: warning: \
shell level (%d) too high, resetting to 1"

void	update_shlvl(t_minishell *data, char *str, int d)
{
	int value;

	value = 0;
	if (str && is_number(str))
		value = ft_atoi(str) + d;
	if (value < 0)
		value = 0;
	if (value > 1000)
	{
		ft_fprintf(STDERR_FILENO, SHLVL_TO_HIGH_ERROR, value + 2);
		value = 0;
	}
	set_env(&data->envp, "SHLVL", ft_itoa(value));
}
