/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_controller.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 15:25:27 by bchabot           #+#    #+#             */
/*   Updated: 2023/01/07 15:19:16 by rlaforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_tab(char **tab)
{
	int	i;

	if (tab == NULL)
		return ;
	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

char	**get_cmd(t_tok *cmds)
{
	char	**args;
	t_tok	*tok;
	int		i;

	tok = cmds;
	i = 0;
	if (!cmds)
		return (NULL);
	while (tok)
	{
		if (*tok->key == '|')
			break ;
		i++;
		tok = tok->next;
	}
	args = malloc(sizeof(char *) * (i + 1));
	tok = cmds;
	i = 0;
	while (tok)
	{
		args[i++] = ft_strdup(tok->value);
		tok = tok->next;
	}
	args[i] = NULL;
	return (args);
}

void	execute_builtins(t_tok *env, t_tok *cmds)
{
	char	**args;

	args = get_cmd(cmds);
	if (ft_strncmp(cmds->value, "export", 7) == 0)
		export(&env, args);
	else if (ft_strncmp(cmds->value, "cd", 7) == 0)
		cd(args, env);
	else if (ft_strncmp(cmds->value, "pwd", 7) == 0)
		pwd();
	else if (ft_strncmp(cmds->value, "env", 7) == 0)
		print_env(&env);
	else if (ft_strncmp(cmds->value, "echo", 7) == 0)
		echo(args);
	free_tab(args);
}

int	is_builtin(char *cmd)
{
	char	*builtins[] = {"echo", "cd", "pwd", "export", "unset", "env", NULL};
	int		i;

	i = 0;	
	while (builtins[i])
	{
		if (ft_strncmp(cmd, builtins[i], ft_strlen(cmd)) == 0)
			return (1);
		i++;
	}
	return (0);
}

char	*strjoin_pipex(char *s1, char *s2)
{
	char	*str;
	int		length;

	if (!s1 || !s2)
		return (NULL);
	length = ft_strlen(s1) + ft_strlen(s2) + 2;
	str = malloc(sizeof(char) * length);
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1, length);
	ft_strlcat(str, "/", length);
	ft_strlcat(str, s2, length);
	return (str);
}

char	*get_path(t_tok *env_tok, char *cmd)
{
	char	**env;
	char	*str;
	int		i;

	if (!cmd || !env_tok)
		return (NULL);
	if (cmd[0] == '/' || cmd[0] == '.')
	{
		str = ft_strdup(cmd);
		if (!access(str, X_OK))
			return (str);
		free(str);
	}
	else
	{
		i = 0;
		env = ft_split(ft_getenv(env_tok, "PATH"), ':');
		while (env[i])
		{
			str = strjoin_pipex(env[i++], cmd);
			if (!access(str, X_OK))
				return (str);
			free(str);
		}
		free_tab(env);
	}
	return (NULL);
}

// 2 strjoin c trop
char	*strjoinlol(char *s1, char *s2)
{
	char	*str;
	int		length;

	if (!s1 || !s2)
		return (NULL);
	length = ft_strlen(s1) + ft_strlen(s2) + 1;
	str = malloc(sizeof(char) * length);
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1, length);
	ft_strlcat(str, s2, length);
	free(s1);
	return (str);
}

//LEAKS-LAND, LE ROYAUME DU LEAK ENTRE VOS MAINS :
char	*fill_tab(t_tok *node)
{
	char	*str;

	str = ft_strdup(node->key);
	str = strjoinlol(str, "=");
	str = strjoinlol(str, node->value);
	return (str);
}

char	**convert_envp(t_tok *head)
{
	t_tok	*node;
	char	**envp;
	int		i;

	node = head;
	i = 0;
	while (node)
	{
		i++;
		node = node->next;
	}
	envp = malloc((i + 1) * sizeof(char *));
	node = head;
	i = 0;
	while (node)
	{
		envp[i++] = fill_tab(node);
		node = node->next;
	}
	envp[i] = NULL;
	return (envp);
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

int	nb_cmds(t_tok *cmds)
{
	t_tok	*tmp;
	int		i;

	tmp = cmds;
	i = 0;
	while (tmp)
	{
		if (*tmp->key == *K_CMD)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

void	child_process(t_tok *env, char **envp, t_tok *cmds)
{
	int	fd_pipe[2];
	int	pid;

	if (pipe(fd_pipe) == -1)
		printf("pipe error\n");
	pid = fork();
	if (pid == -1)
		printf("pid error");
	if (pid == 0)
	{
		close(fd_pipe[0]);
		if (nb_cmds(cmds) != 1)
			dup2(fd_pipe[1], STDOUT_FILENO);
		execute_cmd(env, envp, cmds);
	}
	close(fd_pipe[1]);
	close(fd_pipe[0]);
	if (nb_cmds(cmds) != 1)
		dup2(fd_pipe[0], fd_pipe[1]);
	waitpid(pid, NULL, 0);
}

void	execution_controller(t_tok *env, t_tok *tok_head)
{
	t_tok	*cmds;
	char	**envp;

	if (!tok_head)
		return ;
	cmds = tok_head;
	envp = convert_envp(env);
	while (cmds)
	{
		if (*cmds->key == *K_CMD)
		{
			if (is_builtin(cmds->value))
				execute_builtins(env, cmds);
			else
			{
/*				pid = fork();
				if (pid == -1)
					return ;
				if (pid == 0)
					execute_cmd(env, envp, cmds);
				waitpid(pid, NULL, 0);*/
				child_process(env, envp, cmds);
			}
		}
		cmds = cmds->next;
	}
	free_tab(envp);
}
