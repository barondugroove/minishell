/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchabot <bchabot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 18:41:41 by bchabot           #+#    #+#             */
/*   Updated: 2022/12/12 18:45:43 by bchabot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	unset(t_tok **env_head, char *key)
{
	t_tok	*tmp;

	tmp = *env_head;
	while (tmp->next->key)
	{
		if (ft_strncmp(tmp->next->key, key, ft_strlen(key)) == 0)
		{
			tmp->next = tmp->next->next;
			return ;
		}
		tmp = tmp->next;
	}
}
