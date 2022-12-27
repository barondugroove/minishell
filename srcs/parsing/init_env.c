/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benjaminchabot <benjaminchabot@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 17:26:43 by bchabot           #+#    #+#             */
/*   Updated: 2022/12/27 15:40:03 by benjamincha      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	find_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}

t_tok	*init_env(char **envp)
{
	t_tok	*env_head;
	char	*key;
	char	*value;
	int		i;

	i = 0;
	key = ft_strtok(envp[i], "=");
	value = ft_strtok(NULL, "\0");
	env_head = newtoken(ft_strdup(value), ft_strdup(key));
	while (envp[i])
	{
		key = ft_strtok(envp[i], "=");
		value = ft_strtok(NULL, "\0");
		newtoken_back(&env_head, ft_strdup(value), ft_strdup(key));
		i++;
	}
	return (env_head);
}
