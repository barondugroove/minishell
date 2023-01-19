/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_controller.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 15:25:27 by bchabot           #+#    #+#             */
/*   Updated: 2023/01/19 14:27:45 by rlaforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	execute_builtins(t_allocated *truc, t_tok *cmds)
{
	char	**args;


//
//  NE PAS OUBLIER LES BAD OPTIONS SUR LES BUILTINS
//	pwd -mdr = "pwd: bad option: -m" + exit_code = 1
//	
//	Pour l'instant pwd -mdr = pwd
//
//	if (check_bad_option(args))
//		return (1);

	args = get_cmd(cmds);
	if (ft_strncmp(cmds->value, "export", 7) == 0)
		export(&truc->env, args, cmds);
	else if (ft_strncmp(cmds->value, "cd", 3) == 0)
		cd(args, truc->env, cmds);
	else if (ft_strncmp(cmds->value, "pwd", 4) == 0)
		pwd(truc->env);
	else if (ft_strncmp(cmds->value, "env", 4) == 0)
		print_env(&truc->env);
	else if (ft_strncmp(cmds->value, "echo", 5) == 0)
		echo(args);
	else if (ft_strncmp(cmds->value, "unset", 6) == 0)
		unset(&truc->env, args, cmds);
	free_tab(args);
	return (0);
}

int	execute_cmd(t_allocated *truc, t_tok *cmds)
{
	char	**args;
	char	**envp;
	char	*path;

	args = get_cmd(cmds);
	path = get_path(truc->env, args[0]);
	envp = convert_envp(truc->env);
	if (!path || (execve(path, args, envp) == -1))
	{
		printf("command not found: %s\n", args[0]);
		free(path);
		free_tab(args);
		free_tab(envp);
		free_truc(truc);
		exit (127);
	}
	printf("OUAH LA DINGUERIE, LE BOUT DE CODE QUI SE LANCE JAMAIS\n");
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

int	child_process(t_allocated *truc, t_tok *cmd, int *fd_pipe, int cmd_id)
{
	int	pid;
	int status;
	int fd_save;

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
		if (is_builtin(cmd->value))
		{
			status = execute_builtins(truc, cmd);
			free_truc(truc);
			exit(status);
		}
		status = execute_cmd(truc, cmd);
		if (status != 0)
		{	
			free_truc(truc);
			exit(status);
		}
	}
	else if (cmd_id != 0 && cmd_id != truc->cmd_nbr - 1)
			close(fd_save);
	signal(SIGINT, child_c_handler);
	truc->pids[cmd_id] = pid;
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

void	execution_controller(t_tok *env, t_tok *cmd_head)
{
	t_tok	*cmds;
	t_allocated	truc;
	int		fd_pipe[2];
	int 	status;
	int		i;

	if (!cmd_head)
		return ;
	cmds = cmd_head;
	truc.env = env;
	truc.cmd_head = cmd_head;
	truc.cmd_nbr = nb_cmds(cmds);
	truc.pids = malloc(sizeof(int) * truc.cmd_nbr);
	if (pipe(fd_pipe) == -1)
		printf("error pipe\n");
	i = 0;
	while (i < truc.cmd_nbr)
	{
		if (ft_strncmp(cmds->value, "exit", 5) == 0)
		{
			close(fd_pipe[0]);
			close(fd_pipe[1]);
			free_truc(&truc);
			exit(0);
		}

		child_process(&truc, cmds, fd_pipe, i);
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
	while (i < truc.cmd_nbr)
	{
		waitpid(truc.pids[i++], &status, 0);
		if (WIFEXITED(status))
			exit_code = WEXITSTATUS(status);
	}
	free(truc.pids);
}
