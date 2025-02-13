/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrow.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <romain@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 20:05:55 by romain            #+#    #+#             */
/*   Updated: 2025/02/13 20:10:13 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	display_arrow(const char *color)
{
	ft_fprintf(STDERR_FILENO, color);
	ft_fprintf(STDERR_FILENO, "➜  ");
}
