/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchabot <bchabot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 20:12:45 by bchabot           #+#    #+#             */
/*   Updated: 2023/02/13 15:14:31 by bchabot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	numeric_argument_required(char *arg)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	return ;
}

int	is_valid_number(const char *nptr)
{
	int					i;
	unsigned long long	nbr;
	int					neg;

	i = 0;
	nbr = 0;
	neg = 0;
	if (nptr[0] == '+' || nptr[0] == '-')
	{
		if (nptr[0] == '-')
			neg = 1;
		i++;
	}
	while (nptr[i] && (nptr[i] >= '0') && (nptr[i] <= '9'))
	{
		nbr = nbr * 10 + (nptr[i] - '0');
		if (neg == 0 && nbr > 9223372036854775807)
			return (0);
		if (neg == 1 && nbr > 9223372036854775808ULL)
			return (0);
		i++;
	}
	return (1);
}

int	is_digit(char *args)
{
	int	i;

	i = 1;
	while (args[i])
	{
		if ((!ft_isdigit(args[i]) && args[0] != '-'
				&& args[0] != '+') || !is_valid_number(args))
		{
			numeric_argument_required(args);
			return (2);
		}
		i++;
	}
	return (0);
}

int	check_args(char **args)
{
	int	i;

	if (args[2])
	{
		ft_putstr_fd("exit\n", 1);
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1);
	}
	i = 1;
	while (args[i])
	{
		if (is_digit(args[i]))
			return (2);
		i++;
	}
	return (0);
}
