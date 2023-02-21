/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_controller.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benjaminchabot <benjaminchabot@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 15:25:27 by bchabot           #+#    #+#             */
/*   Updated: 2023/02/21 11:30:10 by benjamincha      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


void	ft_ctrl_back_child(int sig)
{
	(void)sig;
	g_exit_code = 139;

	printf("Quit (core dumped)\n");
}

int	execute_builtins(t_allocated *data, t_tok *cmds, int mode)
{
	char	**args;
	int		status;

	if (has_redir(cmds))
		handle_redirection(data, cmds, mode);
	status = 0;
	args = get_cmd(cmds);
	if (is_builtin(cmds->value) == 1)
		status = cd(args, data->env);
	else if (is_builtin(cmds->value) == 2)
		echo(args);
	else if (is_builtin(cmds->value) == 3)
		status = pwd(args);
	else if (is_builtin(cmds->value) == 4)
		status = export(&data->env, args);
	else if (is_builtin(cmds->value) == 5)
		status = unset(&data->env, args);
	else if (is_builtin(cmds->value) == 6)
		print_env(&data->env);
	else if (is_builtin(cmds->value) == 7)
		status = exit_builtin(args, data);
	free_tab(args);
	return (status);
}

void	execute_cmd(t_allocated *data, t_tok *cmds, int mode)
{
	char	**args;
	char	**envp;
	char	*path;

	if (has_redir(cmds))
		handle_redirection(data, cmds, mode);
	args = get_cmd(cmds);
	check_directory(cmds->value, args, data);
	if (data->cmd_nbr == 1)
	{
		close(data->fd_reset[0]);
		close(data->fd_reset[1]);
	}
	path = get_path(data->env, args[0]);
	envp = convert_envp(data->env);
	if (!path || (execve(path, args, envp) == -1))
	{
		no_cmd_msg(cmds->value, 127);
		free(path);
		free_tab(args);
		free_tab(envp);
		ft_exit(data, 127);
	}
}

void	child_process(t_allocated *data, t_tok *cmd, int *fd_pipe, int cmd_id)
{
	int	pid;
	int	status;
	int	fd_save;

	fd_save = -1;

	if (has_redir(cmd) == 2)
		heredoc_process(data, cmd);
	if (cmd_id != 0 && cmd_id != data->cmd_nbr - 1) // && has_redir(cmd) != 2)
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
		// if (has_redir(cmd) != 2)
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

int	execute_simple_command(t_allocated *data, t_tok *cmd)
{
	int	pid;
	int	status;

	status = 0;

	child_signal_controller();
	if (is_builtin(cmd->value))
	{
		g_exit_code = execute_builtins(data, cmd, 0);
		return (status);
	}
	pid = fork();
	if (pid == -1)
		ft_putstr_fd("pid error", 2);
	else if (pid == 0)
		execute_cmd(data, cmd, 0);
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			g_exit_code = WEXITSTATUS(status);
	}
	return (status);
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

t_allocated	init_data(t_tok *env, t_tok *cmd_head)
{
	t_allocated	data;

	data.env = env;
	data.cmd_head = cmd_head;
	data.cmd_nbr = nb_cmds(cmd_head);
	data.pids = malloc(sizeof(int) * data.cmd_nbr);
	if (data.cmd_nbr == 1)
	{
		data.fd_reset[0] = dup(0);
		data.fd_reset[1] = dup(1);
	}
	return (data);
}

void	execution_controller(t_tok *env, t_tok *cmd_head)
{
	t_tok		*cmds;
	t_allocated	data;
	int			fd_pipe[2];
	int			status;
	int			i;

	if (!cmd_head)
		return ;
	cmds = cmd_head;
	data = init_data(env, cmds);
	if (data.cmd_nbr == 1)
	{
		execute_simple_command(&data, cmds);
		free(data.pids);
		dup_multiple_fds(data.fd_reset, 0, 1);
		close_multiple_fds(data.fd_reset);
		return ;
	}
	if (pipe(fd_pipe) == -1)
		printf("error pipe\n");
	i = -1;
	while (++i < data.cmd_nbr)
	{
		cmds = find_next_cmd(cmds, i);
		child_process(&data, cmds, fd_pipe, i);
	}
	close_multiple_fds(fd_pipe);
	i = -1;
	while (++i < data.cmd_nbr)
	{
		waitpid(data.pids[i], &status, 0);
		if (WIFEXITED(status))
			g_exit_code = WEXITSTATUS(status);
	}
	free(data.pids);
}
