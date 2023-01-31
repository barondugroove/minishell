/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchabot <bchabot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 13:45:58 by benjamincha       #+#    #+#             */
/*   Updated: 2023/01/31 20:51:19 by bchabot          ###   ########.fr       */
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

char	*get_file(t_tok *cmds)
{
	t_tok	*tmp;

	tmp = cmds;
	while (tmp->next)
	{
		if (*tmp->key == '>' && *tmp->next->key == '>')
			return (tmp->next->next->value);
		else if (*tmp->key == '>' || *tmp->key == '<')
			return (tmp->next->value);
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
	if (dir == 0 && access(file, F_OK && R_OK) == 0)
		return (0);
	else if (dir == 1 && access(file, F_OK && W_OK) == 0)
		return (0);
	else
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(file, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (1);
	}
}

t_tok	*get_next_redir(t_tok *cmds, int nbr)
{
	while (cmds)
	{
		if (ft_strcmp(cmds->key, ">>") == 0)
			nbr--;
		else if (*cmds->key == '>' || *cmds->key == '<')
			nbr--;
		ft_putnbr_fd(nbr, 2);
		ft_putstr_fd("\n", 2);
		cmds = cmds->next;
		ft_putstr_fd("next redir is :", 2);
		ft_putstr_fd(cmds->value, 2);
		ft_putstr_fd("\n", 2);
		if (nbr == 0)
			return (cmds);

	}
	return (cmds);
}

void	handle_redirection(t_tok *cmds)
{
	int		fd_in;
	int		fd_out;
	int		nbr;
	char	*str;
	t_tok	*tmp;

	fd_in = -1;
	fd_out = -1;
	nbr = redir_nbr(cmds);
	tmp = cmds;
	while (nbr--)
	{
		str = get_file(tmp);
		if (!str)
			return ;
		if (has_redir(cmds) == 1)
		{
			fd_out = open(str, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			dup2(fd_out, 1);
		}
		if (has_redir(cmds) == 3)
		{
			fd_out = open(str, O_CREAT | O_WRONLY | O_APPEND, 0644);
			dup2(fd_out, 1);
		}
		if (has_redir(cmds) == 2 && !check_file(str, 0))
		{
			fd_in = open(str, O_RDONLY);
			dup2(fd_in, 0);
		}
		if (nbr)
			tmp = get_next_redir(tmp->next, nbr);
		if (fd_in != -1)
			close(fd_in);
		if (fd_out != -1)
			close(fd_out);
	}
}
