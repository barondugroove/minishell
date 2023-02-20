/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_working_dir.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchabot <bchabot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 19:32:16 by bchabot           #+#    #+#             */
/*   Updated: 2023/02/20 20:00:28 by bchabot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	invalid_option(char *arg)
{
	ft_putstr_fd("minishell: pwd: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": invalid option\npwd: usage: pwd [-LP]\n", 2);
	g_exit_code = 1;
	return ;
}

int	pwd(char **args)
{
	char	str[4096];

	if (args[1] && args[1][0] == '-' && ft_strncmp(args[1], "-LP", 4) != 0)
	{
		invalid_option(args[1]);
		return (1);
	}
	getcwd(str, sizeof(str));
	printf("%s\n", str);
	return (0);
}
