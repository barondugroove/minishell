/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchabot <bchabot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 14:47:47 by bchabot           #+#    #+#             */
/*   Updated: 2023/02/08 18:07:30 by bchabot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	error_file(char *file, int errnum)
{
//	ft_putstr_fd(strerror(errnum), 2);
//	ft_putstr_fd(": ", 2);
//	ft_putendl_fd(file, 2);
	(void)errnum;
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
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
	struct stat    path_stat;

	if (dir == 0 && !access(file, F_OK))
	{
		stat(file, &path_stat);
		if (!(path_stat.st_mode & S_IWUSR))
		{
			ft_putstr_fd("minishell: Permission denied\n", 2);
			g_exit_code = 126;
			ft_exit(g_exit_code);
        }
		return (0);
	}
	if (dir == 1)
	{
		if (access(file, F_OK) == -1)
			return (0);
		stat(file, &path_stat);
		if (!(path_stat.st_mode & S_IWUSR))
		{
    		ft_putstr_fd("minishell: Permission denied\n", 2);
	        g_exit_code = 1;
			ft_exit(g_exit_code);
		}
		return (0);
	}
	error_file(file, errno);
	ft_exit(1);
	return (1);
}

t_tok	*get_next_redir(t_tok *cmds, int nbr)
{
	t_tok	*tmp;

	(void)nbr;
	tmp = cmds;
	while (tmp)
	{
		// ft_putstr_fd("tested token is : ", 2);
		// ft_putstr_fd(tmp->value, 2);
		// ft_putstr_fd("\n", 2);
		// ft_putstr_fd("\n", 2);
		// ft_putstr_fd("\n", 2);
		if (ft_strcmp(tmp->key, ">>") == 0 || *tmp->key == '>' || *tmp->key == '<')
		{
			// ft_putstr_fd("next redir is : ", 2);
			// ft_putstr_fd(tmp->value, 2);
			// ft_putstr_fd("\n", 2);
			if (*tmp->next->key == *K_ARG)
				return (tmp);
		}
		tmp = tmp->next;
	}
	// ft_putstr_fd("next redir is : ", 2);
	// ft_putstr_fd(tmp->value, 2);
	// ft_putstr_fd("\n", 2);
	// ft_putstr_fd("next file is : ", 2);
	// ft_putstr_fd(tmp->next->value, 2);
	// ft_putstr_fd("\n", 2);
	// ft_putstr_fd("\n", 2);
	// ft_putstr_fd("\n", 2);
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
