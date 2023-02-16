/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benjaminchabot <benjaminchabot@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 14:47:47 by bchabot           #+#    #+#             */
/*   Updated: 2023/02/15 22:48:49 by benjamincha      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	has_redir(t_tok *cmds)
{
	t_tok	*tmp;

	tmp = cmds;
	while (tmp && *tmp->key != '|')
	{
		if (ft_strcmp(tmp->key, ">>") == 0)
			return (4);
		else if (ft_strcmp(tmp->key, "<<") == 0)
			return (2);
		else if (*tmp->key == '>')
			return (3);
		else if (*tmp->key == '<')
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	redir_nbr(t_tok *cmds)
{
	t_tok	*tmp;
	int		i;

	tmp = cmds;
	i = 0;
	while (tmp->next && *tmp->key != '|')
	{
		if (ft_strcmp(tmp->key, ">>") == 0)
			i++;
		else if (*tmp->key == '>')
			i++;
		else if (*tmp->key == '<')
			i++;
		tmp = tmp->next;
	}
	return (i);
}

t_tok	*get_next_redir(t_tok *cmds)
{
	t_tok	*tmp;

	tmp = cmds;
	while (tmp)
	{
		if (*tmp->key == '>' || *tmp->key == '<')
		{
			if (*tmp->next->key == 'A')
				return (tmp);
		}
		tmp = tmp->next;
	}
	return (tmp);
}

char	*get_file(t_tok *cmds, int nbr)
{
	t_tok	*tmp;
	int		i;

	tmp = cmds;
	i = 0;
	while (tmp->next)
	{
		if (*tmp->key == '>' || *tmp->key == '<')
		{
			if (i == nbr)
				return (tmp->next->value);
			else
				i++;
		}
		tmp = tmp->next;
	}
	return (NULL);
}
