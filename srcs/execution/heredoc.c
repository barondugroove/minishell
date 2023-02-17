/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benjaminchabot <benjaminchabot@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 15:22:58 by bchabot           #+#    #+#             */
/*   Updated: 2023/02/16 23:57:01 by benjamincha      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	launch_heredoc(t_allocated *data, char *delim, int *fd_pipe)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line || !ft_strcmp(line, delim))
			break ;
		ft_putstr_fd(line, fd_pipe[1]);
		ft_putstr_fd("\n", fd_pipe[1]);
	}
	close(fd_pipe[1]);
	close(fd_pipe[0]);
	ft_exit(data, 0);
}

void	wait_heredoc(int pid)
{
	int	status;

	status = 0;
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_exit_code = WEXITSTATUS(status);
	return ;
}

void	heredoc_process(t_allocated *data, t_tok *cmd)
{
	int		pipe_heredoc[2];
	int		pid;

	signal(SIGINT, SIG_DFL);
	pipe(pipe_heredoc);
	pid = fork();
	if (pid == -1)
		ft_putstr_fd("pid error", 2);
	else if (pid == 0)
		launch_heredoc(data, cmd->next->value, pipe_heredoc);
	else
	{
		wait_heredoc(pid);
		if (redir_nbr(cmd->next) == 0)
			dup2(pipe_heredoc[0], 0);
		close(pipe_heredoc[1]);
	}
	signal(SIGINT, child_c_handler);
	return ;
}
