/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_controller.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benjaminchabot <benjaminchabot@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 15:25:27 by bchabot           #+#    #+#             */
/*   Updated: 2023/01/15 17:30:33 by benjamincha      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	execute_builtins(t_tok *env, t_tok *cmds)
{
	char	**args;

	args = get_cmd(cmds);
	if (ft_strncmp(cmds->value, "export", 7) == 0)
		export(&env, args, cmds);
	else if (ft_strncmp(cmds->value, "cd", 3) == 0)
		cd(args, env, cmds);
	else if (ft_strncmp(cmds->value, "pwd", 4) == 0)
		pwd(env);
	else if (ft_strncmp(cmds->value, "env", 4) == 0)
		print_env(&env);
	else if (ft_strncmp(cmds->value, "echo", 5) == 0)
		echo(args);
	else if (ft_strncmp(cmds->value, "unset", 6) == 0)
		unset(&env, args, cmds);
	free_tab(args);
	return (0);
}

int	execute_cmd(t_tok *env, char **envp, t_tok *cmds)
{
	char	**args;
	char	*path;

	args = get_cmd(cmds);
	path = get_path(env, args[0]);
	if (!path || (execve(path, args, envp) == -1))
	{
		printf("command not found: %s\n", args[0]);
		free(path);
		free_tab(args);
		exit (127);
	}
	free(path);
	free_tab(args);
	return (0);
}

void	duplicator(int *fd_pipe, int fd_save, int i, int total)
{
	if (total == 1)
	{
		close(fd_pipe[0]);
		close(fd_pipe[1]);
		return ;
	}		
	if (i == 0)
	{
		if (dup2(fd_pipe[1], STDOUT_FILENO) == -1)
			perror("dup2");
		close(fd_pipe[0]);
		close(fd_pipe[1]);
	}
	else if (i == total - 1)
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

int	child_process(t_tok *env, char **envp, t_tok *cmd, int *fd_pipe, int i, int total)
{
	int	pid;
	int status;
	int fd_save;

	fd_save = -1;
	if (i != 0 && i != total - 1)
    {
		fd_save = dup(fd_pipe[0]);
		close(fd_pipe[0]);
		close(fd_pipe[1]);
		pipe(fd_pipe);
	}
	pid = fork();
	if (pid == -1)
		printf("pid error");
	if (pid == 0)
	{
		duplicator(fd_pipe, fd_save, i, total);
		if (is_builtin(cmd->value))
		{
			status = execute_builtins(env, cmd);
			exit (status);
		}
		else
			execute_cmd(env, envp, cmd);
	}
	else
	{
		if (i != 0 && i != total - 1)
			close(fd_save);
	}
	return (pid);
}

int	has_pipe(t_tok *cmds)
{
	t_tok *tmp;

	tmp = cmds;
	while (tmp->next)
	{
		if (*tmp->key == '|')
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

t_tok	*find_next_cmd(t_tok *cmds)
{
	while (cmds->next)
	{
		cmds = cmds->next;
		if (*cmds->key == *K_CMD)
			return (cmds);
	}
	return (cmds);
}

void	execution_controller(t_tok *env, t_tok *tok_head)
{
	t_tok	*cmds;
	char	**envp;
	int		fd_pipe[2];
	int		*pid;
	int		nbr;
	int		i;

	if (!tok_head)
		return ;
	cmds = tok_head;
	envp = convert_envp(env);
	nbr = nb_cmds(cmds);
	i = 0;
	pid = malloc(sizeof(int) * nb_cmds(cmds));
	if (pipe(fd_pipe) == -1)
		printf("error pipe\n");
	while (i < nbr)
	{
		pid[i] = child_process(env, envp, cmds, fd_pipe, i, nbr);
		cmds = find_next_cmd(cmds);
		i++;
	}
	close(fd_pipe[0]);
	close(fd_pipe[1]);
	i = 0;
	while (pid[i])
	{
		waitpid(pid[i], NULL, 0);
		i++;
	}
	free_tab(envp);
}
