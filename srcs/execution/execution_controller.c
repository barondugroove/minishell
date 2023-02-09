/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_controller.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchabot <bchabot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 15:25:27 by bchabot           #+#    #+#             */
/*   Updated: 2023/02/09 20:53:31 by bchabot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	execute_builtins(t_allocated *data, t_tok *cmds)
{
	char	**args;
	int		status;

	status = 0;
	args = get_cmd(cmds);
	if (ft_strncmp(cmds->value, "export", 7) == 0)
		status = export(&data->env, args);
	else if (ft_strncmp(cmds->value, "cd", 3) == 0)
		status = cd(args, data->env);
	else if (ft_strncmp(cmds->value, "pwd", 4) == 0)
		status = pwd(data->env, args);
	else if (ft_strncmp(cmds->value, "env", 4) == 0)
		print_env(&data->env);
	else if (ft_strncmp(cmds->value, "echo", 5) == 0)
		echo(args);
	else if (ft_strncmp(cmds->value, "unset", 6) == 0)
		status = unset(&data->env, args);
	else if (ft_strncmp(cmds->value, "exit", 5) == 0)
		status = exit_builtin(args, data);
	free_tab(args);
	return (status);
}

void	execute_cmd(t_allocated *data, t_tok *cmds)
{
	char	**args;
	char	**envp;
	char	*path;
	int		status;

	args = get_cmd(cmds);
	status = check_directory(cmds->value);
	if (status)
		exit(status);
	path = get_path(data->env, args[0]);
	envp = convert_envp(data->env);
	if (!path || (execve(path, args, envp) == -1))
	{
		ft_putstr_fd(cmds->value, 2);
		ft_putstr_fd(": command not found", 2);
		ft_putstr_fd("\n", 2);
		free(path);
		free_tab(args);
		free_tab(envp);
		free_allocated(data);
		exit(127);
	}
}

void	duplicator(int *fd_pipe, int fd_save, int cmd_id, int cmd_nbr)
{
	if (cmd_id == 0)
	{
		if (dup2(fd_pipe[1], STDOUT_FILENO) == -1)
			perror("dup2");
		close(fd_pipe[0]);
		close(fd_pipe[1]);
	}
	else if (cmd_id == cmd_nbr - 1)
	{
		if (dup2(fd_pipe[0], STDIN_FILENO) == -1)
			perror("dup2");
		close(fd_pipe[0]);
		close(fd_pipe[1]);
	}
	else
	{
		if (dup2(fd_pipe[1], STDOUT_FILENO) == -1)
			perror("dup2");
		if (dup2(fd_save, STDIN_FILENO) == -1)
			perror("dup2");
		close(fd_save);
		close(fd_pipe[0]);
		close(fd_pipe[1]);
	}
}

void	child_process(t_allocated *data, t_tok *cmd, int *fd_pipe, int cmd_id)
{
	int	pid;
	int	status;
	int	fd_save;

	fd_save = -1;
	signal(SIGINT, SIG_DFL);
	if (cmd_id != 0 && cmd_id != data->cmd_nbr - 1)
	{
		fd_save = dup(fd_pipe[0]);
		close(fd_pipe[0]);
		close(fd_pipe[1]);
		pipe(fd_pipe);
	}
	pid = fork();
	if (pid == -1)
		printf("pid error");
	else if (pid == 0)
	{
		duplicator(fd_pipe, fd_save, cmd_id, data->cmd_nbr);
		if (has_redir(cmd))
			handle_redirection(data, cmd);
		if (is_builtin(cmd->value))
		{
			status = execute_builtins(data, cmd);
			free_allocated(data);
			exit(status);
		}
		execute_cmd(data, cmd);
	}
	else if (cmd_id != 0 && cmd_id != data->cmd_nbr - 1)
		close(fd_save);
	signal(SIGINT, child_c_handler);
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
	signal(SIGINT, child_c_handler);
	if (is_builtin(cmd->value))
	{
		if (has_redir(data->cmd_head))
			handle_redirection(data, cmd);
		g_exit_code = execute_builtins(data, cmd);
		return (status);
	}
	pid = fork();
	if (pid == -1)
		printf("pid error");
	else if (pid == 0)
	{
		if (has_redir(data->cmd_head))
			handle_redirection(data, cmd);
		execute_cmd(data, cmd);
	}
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
		if (*cmds->key == *K_CMD)
		{
			if (i == nbr)
				break ;
			i++;
		}
		cmds = cmds->next;
	}
	if (*cmds->key == '|')
		cmds = cmds->next;
	return (cmds);
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
	i = 0;
	cmds = find_next_cmd(cmd_head, i);
	data.env = env;
	data.cmd_head = cmd_head;
	data.cmd_nbr = nb_cmds(cmds);
	data.pids = malloc(sizeof(int) * data.cmd_nbr);
	if (data.cmd_nbr == 1)
	{
		execute_simple_command(&data, cmds);
		free(data.pids);
		return ;
	}
	if (pipe(fd_pipe) == -1)
		printf("error pipe\n");
	while (i < data.cmd_nbr)
	{
		cmds = find_next_cmd(cmds, i);
		child_process(&data, cmds, fd_pipe, i);
		i++;
	}
	close(fd_pipe[0]);
	close(fd_pipe[1]);
	i = 0;
	while (i < data.cmd_nbr)
	{
		waitpid(data.pids[i++], &status, 0);
		if (WIFEXITED(status))
			g_exit_code = WEXITSTATUS(status);
	}
	free(data.pids);
}
