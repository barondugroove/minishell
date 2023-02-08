/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchabot <bchabot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 13:45:58 by benjamincha       #+#    #+#             */
/*   Updated: 2023/02/08 18:07:30 by bchabot          ###   ########.fr       */
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

int is_dir(const char *path)
{
    struct stat path_stat;
    stat(path, &path_stat);
    return S_ISDIR(path_stat.st_mode);
}


int is_regular_file(const char *path)
{
    struct stat path_stat;
    stat(path, &path_stat);
    return S_ISREG(path_stat.st_mode);
}

int    check_directory(char *command)
{
    struct stat    path_stat;

    if (!access(command, F_OK))
    {
		stat(command, &path_stat);
    	if (!(path_stat.st_mode & S_IXUSR))
       	{
            ft_putstr_fd("minishell: Permission denied", 2);
            g_exit_code = 126;
			ft_exit(g_exit_code);
        }
	}
	else if (is_dir(command))
    {
		g_exit_code = 126;
		ft_putstr_fd("minishell: Is a directory\n", 2);
		ft_exit(g_exit_code);
		return (1);
    }
    else
	{
		ft_putstr_fd(command, 2);
		ft_putstr_fd(": command not found", 2);
		ft_putstr_fd("\n", 2);
		exit(127);
	}
    return (0);
}

void	set_redir_out(t_tok *tmp, int dir, int nbr)
{
	int		fd_out;

	fd_out = -1;
	// ft_putstr_fd("outfile is : ", 2);
	// ft_putstr_fd(tmp->next->value, 2);
	// ft_putstr_fd("\n", 2);
	// ft_putstr_fd("dir is :", 2);
	// ft_putnbr_fd(dir, 2);
	// ft_putstr_fd("\n", 2);
	// ft_putstr_fd("nbr is : ", 2);
	// ft_putnbr_fd(nbr, 2);
	// ft_putstr_fd("\n", 2);
	if (check_file(tmp->next->value, 1))
		return ;
	if (dir == 3)
		fd_out = open(tmp->next->value, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else
		fd_out = open(tmp->next->value, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (nbr == 0)
		dup2(fd_out, 1);
	if (fd_out != -1)
		close(fd_out);
	return ;
}

void	set_redir_in(t_tok *cmd, t_tok *tmp, int dir, int nbr)
{
	int		fd_in;

	(void)dir;
	fd_in = -1;
	// ft_putstr_fd("cmd is : ", 2);
	// ft_putstr_fd(cmd->value, 2);
	// ft_putstr_fd("\n", 2);
	// ft_putstr_fd("infile file is : ", 2);
	// ft_putstr_fd(tmp->next->value, 2);
	// ft_putstr_fd("\n", 2);
	// ft_putstr_fd("is builtin is is : ", 2);
	// ft_putnbr_fd(is_builtin(cmd->value), 2);
	// ft_putstr_fd("\n", 2);
	// ft_putstr_fd("nbr is : ", 2);
	// ft_putnbr_fd(nbr, 2);
	// ft_putstr_fd("\n", 2);
	if (check_file(tmp->next->value, 0))
		return ;
	if (is_builtin(cmd->value) != 2)
		fd_in = open(tmp->next->value, O_RDONLY, 0644);
	else
		return ;
	if (nbr == 0)
		dup2(fd_in, 0);
	if (fd_in != -1)
		close(fd_in);
	return ;
}

int	redir_start(t_tok *cmd)
{
	t_tok	*tmp;

	tmp = cmd;
	while(tmp)
	{
		if (*tmp->key == '<' || *tmp->key == '>')
			return (1);
		else if (*tmp->key == *K_CMD)
			return (0);
		tmp = tmp->next;
	}
	return (0);
}

void	handle_redirection(t_allocated *data, t_tok *cmd)
{
	int		nbr;
	t_tok	*tmp;

	if (redir_start(data->cmd_head))
		tmp = get_next_redir(data->cmd_head, 1);
	else
		tmp = get_next_redir(cmd, 1);
	nbr = redir_nbr(tmp);
	while (nbr--)
	{
		if (has_redir(tmp) > 2)
			set_redir_out(tmp, has_redir(tmp), nbr);
		else if (has_redir(tmp) < 3 && has_redir(tmp) != 0)
			set_redir_in(cmd, tmp, has_redir(tmp), nbr);
		if (nbr)
			tmp = get_next_redir(tmp->next, nbr);
	}
}
