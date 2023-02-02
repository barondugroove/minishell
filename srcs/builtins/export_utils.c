/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchabot <bchabot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 15:23:41 by bchabot           #+#    #+#             */
/*   Updated: 2023/02/02 18:46:14 by bchabot          ###   ########.fr       */
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
	while (tmp)
	{
		newtoken_back(&export, ft_strdup(tmp->value), ft_strdup(tmp->key));
		tmp = tmp->next;
	}
	return (export);
}

int	has_equal(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '=')
			return (1);
		else if (arg[i] == '+' && arg[i + 1] == '=')
			return (2);
		i++;
	}
	return (0);
}

int	is_existing(t_tok **env, char *arg)
{
	t_tok	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, arg) == 0)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
