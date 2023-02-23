/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benjaminchabot <benjaminchabot@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 13:45:58 by benjamincha       #+#    #+#             */
/*   Updated: 2023/02/23 01:07:26 by benjamincha      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	duplicator(int *fd_pipe, int fd_save, int cmd_id, int cmd_nbr)
{
	if (cmd_id == 0)
	{
		if (dup2(fd_pipe[1], STDOUT_FILENO) == -1)
			perror("dup2");
		close_multiple_fds(fd_pipe);
	}
	else if (cmd_id == cmd_nbr - 1)
	{
		if (dup2(fd_pipe[0], STDIN_FILENO) == -1)
			perror("dup2");
		close_multiple_fds(fd_pipe);
	}
	else
	{
		if (dup2(fd_pipe[1], STDOUT_FILENO) == -1)
			perror("dup2");
		if (dup2(fd_save, STDIN_FILENO) == -1)
			perror("dup2");
		close(fd_save);
		close_multiple_fds(fd_pipe);
	}
}

int	set_redir_out(t_tok *tmp, int dir)
{
	int	fd_out;
	int	status;

	fd_out = -1;
	status = check_file(tmp->next->value, 1);
	if (status)
		return (status);
	if (dir == 3)
		fd_out = open(tmp->next->value, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else
		fd_out = open(tmp->next->value, O_CREAT | O_WRONLY | O_APPEND, 0644);
	dup2(fd_out, 1);
	if (fd_out != -1)
		close(fd_out);
	return (0);
}

int	set_redir_in(t_tok *cmd, t_tok *tmp, int dir)
{
	int	fd_in;
	int	status;

	status = 0;
	fd_in = -1;
	if (dir == 1)
		status = check_file(tmp->next->value, 0);
	if (status)
		return (status);
	if (dir == 1 && is_builtin(cmd->value) != 2)
		fd_in = open(tmp->next->value, O_RDONLY, 0644);
	else
		return (0);
	dup2(fd_in, 0);
	if (fd_in != -1)
		close(fd_in);
	return (0);
}

void	handle_redirection(t_allocated *data, t_tok *cmd, int mode)
{
	int		nbr;
	int		status;
	t_tok	*tmp;
	int		fd_pipe[2];

	status = 0;
	tmp = redir_start(data, cmd);
	if (!has_redir(tmp))
		return ;
	pipe(fd_pipe);
	nbr = redir_nbr(tmp);
	while (nbr--)
	{
		if (has_redir(tmp) == 2 && mode == 0)
			heredoc_process(data, tmp, fd_pipe);
		if (has_redir(tmp) > 2)
			status = set_redir_out(tmp, has_redir(tmp));
		else if (has_redir(tmp) == 1)
			status = set_redir_in(cmd, tmp, has_redir(tmp));
		if (status)
			ft_exit(data, status);
		if (nbr)
			tmp = get_next_redir(tmp->next);
	}
	close_multiple_fds(fd_pipe);
}
