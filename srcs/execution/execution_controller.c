/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_controller.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benjaminchabot <benjaminchabot@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 15:25:27 by bchabot           #+#    #+#             */
/*   Updated: 2022/12/27 20:34:58 by benjamincha      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	execute_builtins(t_tok *env, char *cmd)
{
	if (ft_strncmp(cmd, "export", 7) == 0)
		export(&env, NULL);
	else if (ft_strncmp(cmd, "cd", 7) == 0)
		cd("/tmp", env);
	else if (ft_strncmp(cmd, "pwd", 7) == 0)
		pwd();
	else if (ft_strncmp(cmd, "env", 7) == 0)
		print_env(&env);
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

char	*get_path(char **env, char *cmd)
{
	char	*str;
	int	i;

	i = 0;
	if (!cmd)
		return (NULL);
	if (cmd[0] == '/' || cmd[0] == '.')
	{
		str = ft_strdup(cmd);
		if (!access(str, X_OK))
			return (str);
	}
	else
	{
		while (env[i])
		{
			str = strjoin_pipex(env[i], cmd);
			if (!access(str, X_OK))
				return (str);
			free(str);
			i++;
		}
	}
	return (NULL);
}

char	**get_cmd(t_tok *cmds)
{
	char	**args;
	t_tok	*tok;
	int		nb;
	int		i;

	tok = cmds;
	nb = 0;
	i = 0;
	if (!cmds)
		return (NULL);
	while (tok)
	{
		if(*tok->key == '|')
			break;
		nb++;
		tok = tok->next;
	}
	args = malloc(sizeof(char*) * (nb + 1));
	tok = cmds;
	while (i != nb)
	{
		args[i++] = ft_strdup(tok->value);
		tok = tok->next;
	}
	args[nb] = NULL;
	return (args);
}

void	execute_cmd(t_tok *env, t_tok *cmds)
{
	char	**args;
	char	*path;
	t_tok	*tmp;
	char	**env_path;

	tmp = env;
	args = get_cmd(cmds);
	while (tmp)
	{
		if (ft_strncmp(tmp->key, "PATH=", ft_strlen(tmp->key)) == 0)
		{
			env_path = ft_split(tmp->value, ':');
			path = get_path(env_path, args[0]);
			break ;
		}
		tmp = tmp->next;
	}
	if (!path || (execve(path, args, env_path) == -1))
		printf ("Error\n");
}

int is_builtin(char *cmd)
{
	char 	*builtins[] = {"echo", "cd", "pwd", "export", "unset", "env", "exit", NULL};
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

void	execution_controller(t_tok *env, char *prompt)
{
	t_tok	*tok_head;
	t_tok	*cmds;
	int		pid;

	tok_head = parsing_controller(prompt);
	if (!tok_head)
		return ;
	cmds = tok_head;
	print_list(cmds);
	pid = fork();
	if (pid == -1)
		return ;
	while (cmds)
	{
		if (*cmds->key == *K_CMD)
		{
			if (!is_builtin && pid == 0) 
				execute_cmd(env, cmds);
			else
				execute_builtins(env, cmds->value);
		}
		cmds = cmds->next;
	}
	waitpid(pid, NULL, 0);
	free(prompt);
	free_list(tok_head);
}
