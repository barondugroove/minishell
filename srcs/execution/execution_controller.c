/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_controller.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchabot <bchabot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 15:25:27 by bchabot           #+#    #+#             */
/*   Updated: 2023/02/23 19:55:08 by bchabot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	execute_builtins(t_allocated *data, t_tok *cmds, int mode)
{
	char	**args;
	int		status;

	redirection_controller(data, cmds, mode);
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

	redirection_controller(data, cmds, mode);
	if (data->cmd_nbr == 0)
		ft_exit(data, 0);
	args = get_cmd(cmds);
	check_directory(cmds->value, args, data);
	if (data->cmd_nbr <= 1)
		close_multiple_fds(data->fd_reset);
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

t_allocated	init_data(t_tok *env, t_tok *cmd_head, char **prompt)
{
	t_allocated	data;

	data.prompt = prompt;
	data.env = env;
	data.cmd_head = cmd_head;
	data.cmd_nbr = nb_cmds(cmd_head);
	data.pids = malloc(sizeof(int) * data.cmd_nbr);
	if (data.cmd_nbr <= 1)
	{
		data.fd_reset[0] = dup(0);
		data.fd_reset[1] = dup(1);
	}
	return (data);
}

void	execution_controller(t_tok *env, t_tok *cmd_head, char **prompt)
{
	t_tok		*cmds;
	t_allocated	data;

	if (!cmd_head)
		return ;
	cmds = cmd_head;
	data = init_data(env, cmds, prompt);
	if (data.cmd_nbr <= 1)
	{
		execute_simple_command(&data, cmds);
		free(data.pids);
		dup_multiple_fds(data.fd_reset, 0, 1);
		close_multiple_fds(data.fd_reset);
		return ;
	}
	else if (data.cmd_nbr != 0)
		execute_multiple_command(&data, cmds);
}
