/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchabot <bchabot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 15:22:58 by bchabot           #+#    #+#             */
/*   Updated: 2023/02/21 12:46:41 by bchabot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_ctrl_c_heredoc(int sig)
{
	(void)sig;
	g_exit_code = 130;
	// SIGNALS IN HEREDOC NOT FINISHED
	printf("CTRL C IN HEREDOC\n");
	close(0);
}

void	heredoc_signal_controller(void)
{
	signal(SIGINT, ft_ctrl_c_heredoc);
	signal(SIGQUIT, SIG_IGN);
}

void	launch_heredoc(t_allocated *data, char *delim, int *fd_pipe)
{
	char	*line;

	heredoc_signal_controller();
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			ft_putstr_fd("bash: warning: \
			here-document delimited by end-of-file (wanted '", 2);
			ft_putstr_fd(delim, 2);
			ft_putstr_fd("')", 2);
			break ;
		}
		if (!ft_strcmp(line, delim))
			break ;
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
	if (WIFEXITED(status))
		g_exit_code = WEXITSTATUS(status);
	return ;
}

void	heredoc_process(t_allocated *data, t_tok *cmd)
{
	int		pipe_heredoc[2];
	int		pid;
	t_tok	*tmp;

	pipe(pipe_heredoc);
	if (redir_start(data->cmd_head))
		tmp = get_next_redir(data->cmd_head);
	else
		tmp = get_next_redir(cmd);
	pid = fork();
	if (pid == -1)
		ft_putstr_fd("pid error", 2);
	else if (pid == 0)
		launch_heredoc(data, tmp->next->value, pipe_heredoc);
	else
	{
		wait_heredoc(pid);
		if (redir_nbr(cmd->next) == 0)
			dup2(pipe_heredoc[0], 0);
		close_multiple_fds(pipe_heredoc);
	}
	return ;
}
