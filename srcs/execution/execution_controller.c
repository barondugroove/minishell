/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_controller.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benjaminchabot <benjaminchabot@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 15:25:27 by bchabot           #+#    #+#             */
/*   Updated: 2023/01/09 18:10:59 by benjamincha      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	execute_builtins(t_tok *env, t_tok *cmds)
{
	char	**args;

	args = get_cmd(cmds);
	if (ft_strncmp(cmds->value, "export", 7) == 0)
		export(&env, args);
	else if (ft_strncmp(cmds->value, "cd", 3) == 0)
		cd(args, env);
	else if (ft_strncmp(cmds->value, "pwd", 4) == 0)
		pwd();
	else if (ft_strncmp(cmds->value, "env", 4) == 0)
		print_env(&env);
	else if (ft_strncmp(cmds->value, "echo", 5) == 0)
		echo(args);
	else if (ft_strncmp(cmds->value, "unset", 6) == 0)
		unset(&env, args);
	free_tab(args);
}

void	execute_cmd(t_tok *env, char **envp, t_tok *cmds)
{
	char	**args;
	char	*path;

	args = get_cmd(cmds);
	path = get_path(env, args[0]);
	if (!path || (execve(path, args, envp) == -1))
	{
		printf("command not found: %s\n", args[0]);
		free(path);
		free_list(env);
		free_list(cmds);
		free_tab(envp);
		free_tab(args);
		exit(1);
	}
	free(path);
	free_tab(args);
}

void	child_process(t_tok *env, char **envp, t_tok *cmd, int fd_in,
		int fd_out)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		printf("pid error");
	if (pid == 0)
	{
		if (fd_in != STDIN_FILENO)
		{
			dup2(fd_in, STDIN_FILENO);
			close(fd_in);
		}
		if (fd_out != STDOUT_FILENO)
		{
			dup2(fd_out, STDOUT_FILENO);
			close(fd_out);
		}
		if (is_builtin(cmd->value))
			execute_builtins(env, cmd);
		else
			execute_cmd(env, envp, cmd);
	}
	else
	{
		if (fd_out != STDOUT_FILENO)
			close(fd_out);
		if (fd_in != STDIN_FILENO)
			close(fd_in);
		waitpid(pid, NULL, 0);
	}
}

void	execution_controller(t_tok *env, t_tok *tok_head)
{
	t_tok	*cmds;
	char	**envp;
	int		fd_in;
	int		fd_out;
	int		fd_pipe[2];

	if (!tok_head)
		return ;
	cmds = tok_head;
	envp = convert_envp(env);
	while (cmds)
	{
		fd_in = STDIN_FILENO;
		fd_out = STDOUT_FILENO;
		if (*cmds->key == *K_CMD)
		{
			if (nb_cmds(cmds) > 1)
			{
				if (pipe(fd_pipe) == -1)
					printf("error pipe\n");
				fd_out = fd_pipe[1];
			}
			printf("Command executing is '%s' still %d remaining. FD_IN is %d and FD_OUT is %d\n\n", cmds->value, nb_cmds(cmds), fd_in, fd_out);
			child_process(env, envp, cmds, fd_in, fd_out);
			if (nb_cmds(cmds) != 1)
				fd_in = fd_pipe[0];
		}
		cmds = cmds->next;
	}
	if (fd_in != STDIN_FILENO)
		close(fd_in);
	free_tab(envp);
}