/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchabot <bchabot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 16:17:14 by benjamincha       #+#    #+#             */
/*   Updated: 2023/02/14 16:05:54 by bchabot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/***************************************************\
||                                                 ||
||   Need to handle fucking long long :            ||
||    -9 223 372 036 854 775 808 to                ||
||		9 223 372 036 854 775 807                    ||
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

int	exit_builtin(char **args, t_allocated *data)
{
	long long	arg_nbr;
	int			status;

	g_exit_code = 0;
	if (!args[1])
	{
		free_allocated(data);
		free_tab(args);
		ft_exit(0);
	}
	status = check_args(args);
	if (status)
		return (status);
	if (!is_valid_number(args[1]))
		return (2);
	free_allocated(data);
	arg_nbr = ft_atoll(args[1]);
	free_tab(args);
	ft_exit(arg_nbr);
	return (0);
}
