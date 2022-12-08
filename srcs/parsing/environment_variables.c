/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_variables.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchabot <bchabot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 17:26:43 by bchabot           #+#    #+#             */
/*   Updated: 2022/12/08 18:14:16 by bchabot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void add_env_var(t_env_node *env)
{
	(void)env;
}

void	init_env(char **envp)
{
	t_env_node	env;
	int	i;

	i = 0;
	while (envp[i])
	{
		env.key = ft_strtok(envp[i], "=");
		env.value = ft_strtok(envp[i], "\0");
		printf("%s\n", env.key);
		printf("%s\n", env.value);
		i++;
	}
}
