/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 16:17:14 by benjamincha       #+#    #+#             */
/*   Updated: 2023/01/25 16:34:33 by rlaforge         ###   ########.fr       */
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

	i = 1;
	while (args[i])
		i++;
	if (i > 2)
	{
		ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		ft_exit(1);
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
				ft_exit(2);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	exit_builtin(char **args)
{
	long long	arg_nbr;

	g_exit_code = 0;
	if (!args[1])
		ft_exit(0);
	check_args(args);
	arg_nbr = ft_atoll(args[1]);
	if (arg_nbr > INT_MAX || arg_nbr < INT_MIN)
		ft_exit(1);
	else
		ft_exit(arg_nbr);
	return (0);
}
