/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchabot <bchabot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 14:47:47 by bchabot           #+#    #+#             */
/*   Updated: 2023/02/02 17:48:05 by bchabot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	has_redir(t_tok *cmds)
{
	t_tok	*tmp;

	tmp = cmds;
	while (tmp->next && *tmp->key != '|')
	{
		if (*tmp->key == '>')
			return (3);
		else if (ft_strcmp(tmp->key, ">>") == 0)
			return (4);
		else if (ft_strcmp(tmp->key, "<<") == 0)
			return (2);
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

int	check_file(char *file, int dir)
{
	if (dir == 0 && access(file, F_OK | R_OK) == 0)
		return (0);
	if (dir == 1)
	{
		if (access(file, F_OK) == -1)
			return (0);
		if (access(file, W_OK) == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(file, 2);
			ft_putstr_fd(": Permission denied\n", 2);
			ft_exit(1);
			return (1);
		}
		else
			return (0);
	}
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	ft_exit(1);
	return (1);
}

t_tok	*get_next_redir(t_tok *cmds, int nbr)
{
	t_tok	*tmp;
	int		i;

	tmp = cmds;
	i = 0;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, ">>") == 0)
			i++;
		else if (*tmp->key == '>' || *tmp->key == '<')
			i++;
		if (i == nbr)
			return (tmp);
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
		if (ft_strcmp(tmp->key, ">>") == 0 || *tmp->key == '>' || *tmp->key == '<')
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
