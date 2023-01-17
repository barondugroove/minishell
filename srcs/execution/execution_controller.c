/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_controller.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 15:25:27 by bchabot           #+#    #+#             */
/*   Updated: 2023/01/17 12:50:29 by rlaforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	execute_builtins(t_tok *env, t_tok *cmds)
{
	char	**args;


//
//  NE PAS OUBLIER LES BAD OPTIONS SUR LES BUILTINS
//	pwd -mdr = "pwd: bad option: -m"
//	
//	Pour l'instant pwd -mdr = pwd
//
//	if (check_bad_option(args))
//		return (1);

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
	return (1);
}

int	execute_cmd(t_tok *env, t_tok *cmds)
{
	char	**args;
	char	**envp;
	char	*path;

	args = get_cmd(cmds);
	path = get_path(env, args[0]);
	envp = convert_envp(env);
	if (!path || (execve(path, args, envp) == -1))
	{
		printf("command not found: %s\n", args[0]);
		free(path);
		free_tab(args);
		free_tab(envp);
		free_list(env);
		// free cmds HEAD
		// free pids
		exit (127);
	}
	free(path);
	free_tab(args);
	free_tab(envp);
	return (0);
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

int	child_process(int *pidos, int *pids, t_tok *env, t_tok *cmd, t_tok *tok_head, int *fd_pipe, int cmd_id, int cmd_nbr)
{
	int	pid;
	int status;
	int fd_save;

	fd_save = -1;
	if (cmd_id != 0 && cmd_id != cmd_nbr - 1)
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
		duplicator(fd_pipe, fd_save, cmd_id, cmd_nbr);
		if (is_builtin(cmd->value))
		{
			status = execute_builtins(env, cmd);
			free(pids);
			free_list(tok_head);
			free_list(env);
			exit(status);
		}
		status = execute_cmd(env, cmd);
		if (status != 0)
		{
			free(pids);
			free_list(env);
			free_list(tok_head);
			exit(status);
		}
	}
	else if (cmd_id != 0 && cmd_id != cmd_nbr - 1)
			close(fd_save);
	*pidos = pid;
	return (status);
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

void	execution_controller(t_tok *env, t_tok *tok_head)
{
	t_tok	*cmds;
	int		fd_pipe[2];
	int		*pids;
	int		cmd_nbr;
	int status;
	int		i;

	if (!tok_head)
		return ;
	cmds = tok_head;
	cmd_nbr = nb_cmds(cmds);
	i = 0;
	pids = malloc(sizeof(int) * cmd_nbr);
	if (pipe(fd_pipe) == -1)
		printf("error pipe\n");
	while (i < cmd_nbr)
	{
		child_process(&pids[i], pids, env, cmds, tok_head, fd_pipe, i, cmd_nbr);
		while (cmds->next)
		{
			cmds = cmds->next;
			if (*cmds->key == *K_CMD)
				break;
		}
		i++;
	}
	close(fd_pipe[0]);
	close(fd_pipe[1]);
	i = 0;
	while (i < cmd_nbr)
	{
		waitpid(pids[i++], &status, 0);
		if (WIFEXITED(status))
			exit_code = WEXITSTATUS(status);
	}
	free(pids);
}
