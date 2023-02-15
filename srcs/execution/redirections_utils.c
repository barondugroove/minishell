/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchabot <bchabot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 14:47:47 by bchabot           #+#    #+#             */
/*   Updated: 2023/02/15 14:47:13 by bchabot          ###   ########.fr       */
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

void	check_file(char *file, int dir)
{
	struct stat	path_stat;

	if (dir == 0 && !access(file, F_OK))
	{
		stat(file, &path_stat);
		if (!(path_stat.st_mode & S_IWUSR))
		{
			permission_denied_msg(file, 126);
			ft_exit(g_exit_code);
		}
		return ;
	}
	if (dir == 1)
	{
		if (access(file, F_OK) == -1)
			return ;
		stat(file, &path_stat);
		if (!(path_stat.st_mode & S_IWUSR))
		{
			permission_denied_msg(file, 1);
			ft_exit(g_exit_code);
		}
		return ;
	}
	no_file_msg(file, 1);
	ft_exit(1);
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
