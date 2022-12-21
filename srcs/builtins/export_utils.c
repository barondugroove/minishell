/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchabot <bchabot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 15:23:41 by bchabot           #+#    #+#             */
/*   Updated: 2022/12/21 19:50:15 by bchabot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_sorted(t_tok **env_head)
{
	t_tok	*tmp;

	tmp = *env_head;
	while (tmp->next)
	{
		if (ft_strncmp(tmp->key, tmp->next->key, ft_strlen(tmp->key)) > 0)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

void	sort_export(t_tok **env_head)
{
	t_tok	*tmp;
	char	*buf;

	tmp = *env_head;
	while (!is_sorted(env_head))
	{
		if (!tmp->next)
			tmp = *env_head;
		if (ft_strncmp(tmp->key, tmp->next->key, ft_strlen(tmp->key)) > 0)
		{
			buf = tmp->key;
			tmp->key = tmp->next->key;
			tmp->next->key = buf;
			buf = tmp->value;
			tmp->value = tmp->next->value;
			tmp->next->value = buf;
		}
		tmp = tmp->next;
	}
}

t_tok	*dup_env(t_tok **env_head)
{
	t_tok	*tmp;
	t_tok	*export;

	tmp = *env_head;
	export = newnode(ft_strdup(tmp->key), ft_strdup(tmp->value));
	tmp = tmp->next;
	while (tmp)
	{
		newnode_back(&export, ft_strdup(tmp->value), ft_strdup(tmp->key));
		tmp = tmp->next;
	}
	return (export);
}
