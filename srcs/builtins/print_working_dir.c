/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_working_dir.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchabot <bchabot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 19:32:16 by bchabot           #+#    #+#             */
/*   Updated: 2023/02/20 14:47:26 by bchabot          ###   ########.fr       */
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

int	pwd(t_tok *env, char **args)
{
	char	*str;

	if (args[1] && args[1][0] == '-' && ft_strncmp(args[1], "-LP", 4) != 0)
	{
		invalid_option(args[1]);
		return (1);
	}
	str = ft_strdup(ft_getenv(env, "PWD"));
	printf("%s\n", str);
	free(str);
	return (0);
}
