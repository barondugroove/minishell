/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_with_pipes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchabot <bchabot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 20:38:41 by bchabot           #+#    #+#             */
/*   Updated: 2023/02/23 15:50:06 by bchabot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_tok	*find_next_cmd(t_tok *cmds, int nbr)
{
	int	i;

	i = 0;
	if (!cmds)
		return (NULL);
	while (cmds && *cmds->key != '|')
	{
		if (*cmds->key == *K_CMD && i++ == nbr)
			break ;
		cmds = cmds->next;
	}
	if (cmds && *cmds->key == '|')
		cmds = cmds->next;
	return (cmds);
}

int	has_pipe(t_tok *cmds)
{
	t_tok	*tmp;

	tmp = cmds;
	while (tmp->next)
	{
		if (*tmp->key == '|')
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	handle_child(t_allocated *data, t_tok *cmd, int *status)
{
	if (is_builtin(cmd->value))
	{
		*status = execute_builtins(data, cmd, 1);
		ft_exit(data, *status);
	}
	execute_cmd(data, cmd, 1);
}

void	child_process(t_allocated *data, t_tok *cmd, int *fd_pipe, int cmd_id)
{
	int	pid;
	int	status;
	int	fd_save;

	if (cmd_id != 0 && cmd_id != data->cmd_nbr - 1)
	{
		fd_save = dup(fd_pipe[0]);
		close_multiple_fds(fd_pipe);
		pipe(fd_pipe);
	}
	heredoc_process(data, cmd, fd_pipe);
	pid = fork();
	if (pid == -1)
		ft_putstr_fd("pid error", 2);
	else if (pid == 0)
	{
		duplicator(fd_pipe, fd_save, cmd_id, data->cmd_nbr);
		handle_child(data, cmd, &status);
	}
	else if (cmd_id != 0 && cmd_id != data->cmd_nbr - 1)
		close(fd_save);
	data->pids[cmd_id] = pid;
}

void	execute_multiple_command(t_allocated *data, t_tok *cmds)
{
	int	fd_pipe[2];
	int	status;
	int	i;

	if (pipe(fd_pipe) == -1)
		printf("error pipe\n");
	i = -1;
	while (++i < data->cmd_nbr)
	{
		cmds = find_next_cmd(cmds, i);
		child_process(data, cmds, fd_pipe, i);
	}
	close_multiple_fds(fd_pipe);
	i = -1;
	while (++i < data->cmd_nbr)
	{
		waitpid(data->pids[i], &status, 0);
		if (WIFEXITED(status))
			g_exit_code = WEXITSTATUS(status);
	}
	free(data->pids);
}
