/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_with_pipes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchabot <bchabot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 20:38:41 by bchabot           #+#    #+#             */
/*   Updated: 2023/02/21 20:46:21 by bchabot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_ctrl_back_child(int sig)
{
	(void)sig;
	g_exit_code = 139;
	printf("Quit (core dumped)\n");
}

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

void	child_process(t_allocated *data, t_tok *cmd, int *fd_pipe, int cmd_id)
{
	int	pid;
	int	status;
	int	fd_save;

	fd_save = -1;
	heredoc_process(data, cmd);
	if (cmd_id != 0 && cmd_id != data->cmd_nbr - 1)
	{
		fd_save = dup(fd_pipe[0]);
		close_multiple_fds(fd_pipe);
		pipe(fd_pipe);
	}
	pid = fork();
	if (pid == -1)
		ft_putstr_fd("pid error", 2);
	else if (pid == 0)
	{
		duplicator(fd_pipe, fd_save, cmd_id, data->cmd_nbr);
		if (is_builtin(cmd->value))
		{
			status = execute_builtins(data, cmd, 1);
			ft_exit(data, status);
		}
		execute_cmd(data, cmd, 1);
	}
	else if (cmd_id != 0 && cmd_id != data->cmd_nbr - 1)
		close(fd_save);
	data->pids[cmd_id] = pid;
}
