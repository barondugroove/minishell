/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benjaminchabot <benjaminchabot@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 16:17:14 by benjamincha       #+#    #+#             */
/*   Updated: 2023/02/09 01:32:24 by benjamincha      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/***************************************************\
||                                                 ||
||   Need to handle fucking long long :            ||
||    -9 223 372 036 854 775 808 to                ||
||	  9 223 372 036 854 775 807                    ||
||                                                 ||
||                                                 ||
\***************************************************/

void	ft_exit(long long code)
{
	g_exit_code = code;
	exit(code);
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

static void	numeric_argument_required(char *arg)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	return ;
}

int	check_args(char **args)
{
	int	i;
	int	j;

	if (args[2])
	{
		ft_putstr_fd("exit\n", 1);
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1);
	}
	i = 1;
	while (args[i])
	{
		j = 0;
		while (args[i][j])
		{
			if (!ft_isdigit(args[i][j]) && (args[i][j] != '+' && args[i][j] != '-'))
			{
				numeric_argument_required(args[i]);
				return (2);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	exit_builtin(char **args, t_allocated *data)
{
	long long	arg_nbr;
	int			status;

	g_exit_code = 0;
	if (!args[1])
		return (0);
	status = check_args(args);
	if (status)
		return (status);
	if (!is_valid_number(args[1]))
	{
		numeric_argument_required(args[1]);
		return (2);
	}
	free_allocated(data);
	arg_nbr = ft_atoll(args[1]);
	free_tab(args);
	ft_exit(arg_nbr);
	return (0);
}
