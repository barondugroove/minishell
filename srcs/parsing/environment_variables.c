/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_variables.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchabot <bchabot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 17:26:43 by bchabot           #+#    #+#             */
/*   Updated: 2022/12/07 17:43:41 by bchabot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_env(char **envp)
{
//	t_env	env;
	int	i;

	i = 0;
	while (envp[i])
		printf("%s\n", envp[i++]);
}
