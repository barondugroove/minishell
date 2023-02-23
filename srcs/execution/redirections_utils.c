/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchabot <bchabot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 14:47:47 by bchabot           #+#    #+#             */
/*   Updated: 2023/02/23 20:41:29 by bchabot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_tok	*redir_start(t_allocated *data, t_tok *cmd)
{
	t_tok	*tmp;

	tmp = data->cmd_head;
	while (tmp)
	{
		if (*tmp->key == '<' || *tmp->key == '>')
		{
			tmp = get_next_redir(data->cmd_head);
			break ;
		}
		else if (*tmp->key == *K_CMD)
		{
			tmp = get_next_redir(cmd);
			break ;
		}
		tmp = tmp->next;
	}
	return (tmp);
}

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
		if (*tmp->key == '>')
			i++;
		if (*tmp->key == '<')
			i++;
		tmp = tmp->next;
	}
	return (i);
}

t_tok	*get_next_redir(t_tok *cmds)
{
	t_tok	*tmp;

	tmp = cmds;
	while (tmp && *tmp->key != '|')
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
