/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchabot <bchabot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 17:26:43 by bchabot           #+#    #+#             */
/*   Updated: 2022/12/19 17:42:32 by bchabot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_tok	*init_env(char **envp)
{
	t_tok	*env_head;
	char	*key;
	char	*value;
	int		i;

	i = 0;
	env_head = malloc(sizeof(t_tok));
	env_head->key = ft_strtok(envp[i++], "=");
	env_head->value = ft_strtok(NULL, "\0");
	env_head->next = NULL;
	while (envp[i])
	{
		key = ft_strtok(envp[i], "=");
		value = ft_strtok(NULL, "\0");
		newnode_back(&env_head, value, key);
		i++;
	}
	return (env_head);
}
