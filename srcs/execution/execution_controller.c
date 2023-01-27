/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_controller.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 15:25:27 by bchabot           #+#    #+#             */
/*   Updated: 2023/01/27 14:43:16 by rlaforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	execute_builtins(t_allocated *truc, t_tok *cmds)
{
	char	**args;
	int		status;

	status = 0;
	args = get_cmd(cmds);
	if (ft_strncmp(cmds->value, "export", 7) == 0)
		status = export(&truc->env, args);
	else if (ft_strncmp(cmds->value, "cd", 3) == 0)
		status = cd(args, truc->env);
	else if (ft_strncmp(cmds->value, "pwd", 4) == 0)
		status = pwd(truc->env, args);
	else if (ft_strncmp(cmds->value, "env", 4) == 0)
		print_env(&truc->env);
	else if (ft_strncmp(cmds->value, "echo", 5) == 0)
		echo(args);
	else if (ft_strncmp(cmds->value, "unset", 6) == 0)
		unset(&truc->env, args, cmds);
	else if (ft_strncmp(cmds->value, "exit", 5) == 0)
		status = exit_builtin(args);
	free_tab(args);
	return (status);
}

void	execute_cmd(t_allocated *truc, t_tok *cmds)
{
	char	**args;
	char	**envp;
	char	*path;

	args = get_cmd(cmds);
	path = get_path(truc->env, args[0]);
	envp = convert_envp(truc->env);
	if (!path || (execve(path, args, envp) == -1))
	{
		ft_putstr_fd(args[0], 2);
		ft_putstr_fd(": command not found", 2);
		ft_putstr_fd("\n", 2);
		free(path);
		free_tab(args);
		free_tab(envp);
		free_truc(truc);
		exit(127);
	}
}

void	duplicator(int *fd_pipe, int fd_save, int cmd_id, int cmd_nbr)
{
	if (cmd_nbr == 1)
	{
		close(fd_pipe[0]);
		close(fd_pipe[1]);
		return ;
	}
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

void	child_process(t_allocated *truc, t_tok *cmd, int *fd_pipe, int cmd_id)
{
	int	pid;
	int	status;
	int	fd_save;

	fd_save = -1;
	if (cmd_id != 0 && cmd_id != truc->cmd_nbr - 1)
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
		duplicator(fd_pipe, fd_save, cmd_id, truc->cmd_nbr);
		if (has_redir(cmd))
			handle_redirection(cmd);
		if (is_builtin(cmd->value))
		{
			status = execute_builtins(truc, cmd);
			free_truc(truc);
			exit(status);
		}
		execute_cmd(truc, cmd);
	}
	else if (cmd_id != 0 && cmd_id != truc->cmd_nbr - 1)
		close(fd_save);
	signal(SIGINT, child_c_handler);
	truc->pids[cmd_id] = pid;
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

int	execute_simple_command(t_allocated *truc, t_tok *cmd)
{
	int	pid;
	int	status;

	if (is_builtin(cmd->value))
	{
		g_exit_code = execute_builtins(truc, cmd);
		return (0);
	}
	pid = fork();
	if (pid == -1)
		printf("pid error");
	else if (pid == 0)
	{
		if (has_redir(cmd))
			handle_redirection(cmd);
		execute_cmd(truc, cmd);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			g_exit_code = WEXITSTATUS(status);
	}
	signal(SIGINT, child_c_handler);
	return (status);
}

void	execution_controller(t_tok *env, t_tok *cmd_head)
{
	t_tok		*cmds;
	t_allocated	truc;
	int			fd_pipe[2];
	int			status;
	int			i;

	if (!cmd_head)
		return ;
	cmds = cmd_head;
	truc.env = env;
	truc.cmd_head = cmd_head;
	truc.cmd_nbr = nb_cmds(cmds);
	truc.pids = malloc(sizeof(int) * truc.cmd_nbr);
	i = 0;
	if (truc.cmd_nbr == 1)
	{
		execute_simple_command(&truc, cmds);
		free(truc.pids);
		return ;
	}
	if (pipe(fd_pipe) == -1)
		printf("error pipe\n");
	while (i < truc.cmd_nbr)
	{
		child_process(&truc, cmds, fd_pipe, i);
		while (cmds->next)
		{
			cmds = cmds->next;
			if (*cmds->key == *K_CMD)
				break ;
		}
		i++;
	}
	close(fd_pipe[0]);
	close(fd_pipe[1]);
	i = 0;
	while (i < truc.cmd_nbr)
	{
		waitpid(truc.pids[i++], &status, 0);
		if (WIFEXITED(status))
			g_exit_code = WEXITSTATUS(status);
	}
	free(truc.pids);
}
