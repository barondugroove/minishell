/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchabot <bchabot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 15:22:58 by bchabot           #+#    #+#             */
/*   Updated: 2023/02/15 16:50:41 by bchabot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	launch_heredoc(char *delim, int *fd_pipe)
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
	return ;
}

int	heredoc_process(t_allocated *data, t_tok *cmd)
{
	int		pipe_heredoc[2];
	int		pid;
	int		status;

	signal(SIGINT, SIG_DFL);
	pipe(pipe_heredoc);
	pid = fork();
	if (pid == -1)
		ft_putstr_fd("pid error", 2);
	else if (pid == 0)
	{
		launch_heredoc(cmd->next->value, pipe_heredoc);
		free_allocated(data);
		ft_exit(0);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			g_exit_code = WEXITSTATUS(status);
		if (redir_nbr(cmd->next) == 0)
			dup2(pipe_heredoc[0], 0);
		close(pipe_heredoc[1]);
	}
	signal(SIGINT, child_c_handler);
	return (pipe_heredoc[0]);
}
