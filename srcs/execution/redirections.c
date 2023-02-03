/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchabot <bchabot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 13:45:58 by benjamincha       #+#    #+#             */
/*   Updated: 2023/02/03 17:58:53 by bchabot          ###   ########.fr       */
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

int	set_redir_out(t_tok *tmp, int dir, int nbr)
{
	int		fd_out;

	fd_out = -1;
	ft_putstr_fd("outfile is : ", 2);
	ft_putstr_fd(tmp->next->value, 2);
	ft_putstr_fd("\n", 2);
	ft_putstr_fd("is builtin is is : ", 2);
	ft_putnbr_fd(is_builtin(tmp->value), 2);
	ft_putstr_fd("\n", 2);
	ft_putstr_fd("nbr is : ", 2);
	ft_putnbr_fd(nbr, 2);
	ft_putstr_fd("\n", 2);
	if (check_file(tmp->next->value, 1))
		return (fd_out);
	if (dir == 3)
		fd_out = open(tmp->next->value, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else
		fd_out = open(tmp->next->value, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (nbr == 0)
		dup2(fd_out, 1);
	return (fd_out);
}

int	set_redir_in(t_allocated *data, t_tok *tmp, int dir, int nbr)
{
	int		fd_in;
	t_tok	*cmds;

	(void)dir;
	cmds = data->cmd_head;
	cmds = find_next_cmd(data->cmd_head);
	fd_in = -1;
	ft_putstr_fd("infile file is : ", 2);
	ft_putstr_fd(tmp->next->value, 2);
	ft_putstr_fd("\n", 2);
	ft_putstr_fd("is builtin is is : ", 2);
	ft_putnbr_fd(is_builtin(cmds->value), 2);
	ft_putstr_fd("\n", 2);
	ft_putstr_fd("nbr is : ", 2);
	ft_putnbr_fd(nbr, 2);
	ft_putstr_fd("\n", 2);
	if (check_file(tmp->next->value, 0))
		return (fd_in);
	fd_in = open(tmp->next->value, O_RDONLY, 0644);
	if (nbr == 0 && is_builtin(cmds->value) != 2)
		dup2(fd_in, 0);
	return (fd_in);
}

void	handle_redirection(t_allocated *data)
{
	int		fd_in;
	int		fd_out;
	int		nbr;
	t_tok	*tmp;

	fd_in = -1;
	fd_out = -1;
	nbr = redir_nbr(data->cmd_head);
	tmp = get_next_redir(data->cmd_head, 1);
	while (nbr--)
	{
		ft_putstr_fd("has redir is : ", 2);
		ft_putnbr_fd(has_redir(tmp), 2);
		ft_putstr_fd("\n", 2);
		if (has_redir(tmp) > 2)
			fd_out = set_redir_out(tmp, has_redir(tmp), nbr);
		else if (has_redir(tmp) < 3 && has_redir(tmp) != 0)
			fd_in = set_redir_in(data, tmp, has_redir(tmp), nbr);
		if (nbr)
			tmp = get_next_redir(tmp->next, nbr);
		if (fd_in != -1)
			close(fd_in);
		if (fd_out != -1)
			close(fd_out);
	}
}
