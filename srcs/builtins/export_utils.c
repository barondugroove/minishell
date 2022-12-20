/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchabot <bchabot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 15:23:41 by bchabot           #+#    #+#             */
/*   Updated: 2022/12/20 15:59:58 by bchabot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_struct(t_tok *head)
{
	t_tok	*tmp;

	tmp = head;
	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp);
	}
	free(head);
}

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
	export = ft_calloc(sizeof(t_tok), 1);
	if (!export)
		return (NULL);
	export->key = tmp->key;
	export->value = tmp->value;
	export->next = NULL;
	tmp = tmp->next;
	while (tmp->next)
	{
		addback_envnode(&export, tmp->value, tmp->key);
		tmp = tmp->next;
	}
	return (export);
}
