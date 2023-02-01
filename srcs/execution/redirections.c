/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchabot <bchabot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 13:45:58 by benjamincha       #+#    #+#             */
/*   Updated: 2023/02/01 17:49:03 by bchabot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/***************************************************\
||                                                 ||
||   Need to handle multiple redir like :          ||
||    - ls > lol >> lol2                           ||
||    creates both files but only fill lol2        ||
||                                                 ||
||   Need to handle here_doc                       ||
||   Need to handle multiple file args like :      ||
||    - cat <./files/infile_big ./files/infile     ||
||                                                 ||
\***************************************************/

void	error_file(char *file, int errnum)
{
	ft_putstr_fd(strerror(errnum), 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(file, 2);
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

int	has_redir(t_tok *cmds)
{
	t_tok	*tmp;

	tmp = cmds;
	while (tmp->next && *tmp->key != '|')
	{
		if (ft_strcmp(tmp->key, ">>") == 0)
			return (3);
		else if (*tmp->key == '>')
			return (1);
		else if (*tmp->key == '<')
			return (2);
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
	// ft_putstr_fd("File in checkfile is :", 2);
	// ft_putstr_fd(file, 2);
	// ft_putstr_fd("\n", 2);
	if (dir == 0 && access(file, F_OK | R_OK) == 0)
		return (0);
	if (dir == 1)
	{
		// ft_putnbr_fd(access(file, F_OK), 2);
		// ft_putstr_fd("\n", 2);
        if (access(file, F_OK) == -1)
			return (0);
		// ft_putnbr_fd(access(file, W_OK), 2);
		// ft_putstr_fd("\n", 2);
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

void	handle_redirection(t_tok *cmds)
{
	int		fd_in;
	int		fd_out;
	int		nbr;
	t_tok	*tmp;

	fd_in = -1;
	fd_out = -1;
	nbr = redir_nbr(cmds);
	tmp = get_next_redir(cmds, 1);
	// ft_putstr_fd("first redir is :", 2);
	// ft_putstr_fd(tmp->value, 2);
	// ft_putstr_fd("\n", 2);
	while (nbr--)
	{
		// ft_putstr_fd("cmd is : ", 2);
		// ft_putstr_fd(cmds->value, 2);
		// ft_putstr_fd("\n", 2);
		// ft_putstr_fd("has redir is : ", 2);
		// ft_putnbr_fd(has_redir(tmp), 2);
		// ft_putstr_fd("\n", 2);
		if (has_redir(tmp) == 1 && !check_file(tmp->next->value, 1))
		{
			// ft_putstr_fd("outfile file is : ", 2);
			// ft_putstr_fd(tmp->next->value, 2);
			// ft_putstr_fd("\n", 2);
			fd_out = open(tmp->next->value, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			if (nbr == 0)
				dup2(fd_out, 1);
		}
		if (has_redir(tmp) == 3 && !check_file(tmp->next->value, 1))
		{
			// ft_putstr_fd("append file is : ", 2);
			// ft_putstr_fd(tmp->next->value, 2);
			// ft_putstr_fd("\n", 2);
			fd_out = open(tmp->next->value, O_CREAT | O_WRONLY | O_APPEND, 0644);
			if (nbr == 0)
				dup2(fd_out, 1);
		}
		if (has_redir(tmp) == 2 && !check_file(tmp->next->value, 0)  && nbr == 0)
		{
			// ft_putstr_fd("infile is : ", 2);
			// ft_putstr_fd(tmp->next->value, 2);
			// ft_putstr_fd("\n", 2);
			fd_in = open(tmp->next->value, O_RDONLY);
			if (nbr == 0)
				dup2(fd_in, 0);
		}
		if (nbr)
		{
			tmp = get_next_redir(tmp->next, nbr);
			// ft_putstr_fd("next redir is :", 2);
			// ft_putstr_fd(tmp->value, 2);
			// ft_putstr_fd("\n", 2);
			cmds = find_next_cmd(cmds);
		}
		if (fd_in != -1)
			close(fd_in);
		if (fd_out != -1)
			close(fd_out);
	}
}
