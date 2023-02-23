/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchabot <bchabot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 15:22:58 by bchabot           #+#    #+#             */
/*   Updated: 2023/02/23 19:52:17 by bchabot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	heredoc_signal_controller(void)
{
	signal(SIGINT, ft_ctrl_c_heredoc);
	signal(SIGQUIT, SIG_IGN);
}

void	empty_line(t_allocated *data, char *delim, int *fd_pipe)
{
	if (g_exit_code != -2)
	{
		ft_putstr_fd("bash: warning: \
		here-document delimited by end-of-file (wanted '", 2);
		ft_putstr_fd(delim, 2);
		ft_putstr_fd("')\n", 2);
		close_multiple_fds(fd_pipe);
		ft_exit(data, 0);
	}
	ft_exit(data, -2);
}

void	launch_heredoc(t_allocated *data, char *delim, int *fd_pipe)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!ft_strcmp(line, delim))
			break ;
		if (!line)
		{
			empty_line(data, delim, fd_pipe);
			break ;
		}
		ft_putstr_fd(line, fd_pipe[1]);
		ft_putstr_fd("\n", fd_pipe[1]);
	}
	close_multiple_fds(fd_pipe);
	ft_exit(data, 0);
}

void	wait_heredoc(int pid)
{
	int	status;

	status = 0;
	waitpid(pid, &status, 0);
	if (g_exit_code == -2)
	{
		g_exit_code = 130;
		return ;
	}
	if (WIFEXITED(status))
		g_exit_code = WEXITSTATUS(status);
	return ;
}

int	heredoc_process(t_allocated *data, t_tok *cmd, int *fd_pipe)
{
	int		pipe_heredoc[2];
	int		pid;

	heredoc_signal_controller();
	if (has_redir(cmd) != 2)
		return (1);
	pipe(pipe_heredoc);
	pid = fork();
	if (pid == -1)
		ft_putstr_fd("pid error", 2);
	else if (pid == 0)
	{
		close_multiple_fds(fd_pipe);
		launch_heredoc(data, cmd->next->value, pipe_heredoc);
	}
	else
	{
		wait_heredoc(pid);
		if (redir_nbr(cmd->next) == 0 && data->cmd_nbr != 0)
			dup2(pipe_heredoc[0], 0);
		close_multiple_fds(pipe_heredoc);
	}
	return (g_exit_code);
}
