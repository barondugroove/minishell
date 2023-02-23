/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchabot <bchabot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 16:17:14 by bchabot           #+#    #+#             */
/*   Updated: 2023/02/23 20:41:58 by bchabot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_exit(t_allocated *data, long long code)
{
	g_exit_code = code;
	free_allocated(data);
	exit(code);
}

long long	ft_atoll(const char *str)
{
	int			i;
	int			neg;
	long long	nbr;

	i = 0;
	neg = 1;
	nbr = 0;
	while (str[i] <= 32)
		++i;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			neg = -1;
		++i;
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		nbr = nbr * 10 + (str[i] - '0');
		++i;
	}
	return (neg * nbr);
}

int	exit_builtin(char **args, t_allocated *data)
{
	long long	arg_nbr;
	int			status;

	if (!args[1])
	{
		free_tab(args);
		ft_exit(data, g_exit_code);
	}
	g_exit_code = 0;
	status = check_args_exit(args);
	if (status)
		return (status);
	if (!is_valid_number(args[1]))
		return (2);
	arg_nbr = ft_atoll(args[1]);
	free_tab(args);
	ft_exit(data, arg_nbr);
	return (0);
}
