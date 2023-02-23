/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchabot <bchabot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 23:29:47 by bchabot           #+#    #+#             */
/*   Updated: 2023/02/23 20:41:53 by bchabot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_n(char *args)
{
	int	i;

	i = 0;
	if (!args)
		return (-1);
	if (args[0] == '-')
		i++;
	else
		return (0);
	while (args[i])
	{
		if (args[i++] != 'n')
			return (0);
	}
	return (1);
}

void	echo(char **args)
{
	int	i;

	i = 1;
	while (args[i] && is_n(args[i]))
		i++;
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (!args[1] || !is_n(args[1]))
		ft_putstr_fd("\n", 1);
}
