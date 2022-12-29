/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_controller.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 15:25:27 by bchabot           #+#    #+#             */
/*   Updated: 2022/12/30 00:23:19 by rlaforge         ###   ########.fr       */
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
	int		nb;
	int		i;

	tok = cmds;
	nb = 0;
	i = 0;
	if (!cmds)
		return (NULL);
	while (tok)
	{
		if (*tok->key == '|')
			break ;
		nb++;
		tok = tok->next;
	}
	args = malloc(sizeof(char *) * (nb + 1));
	tok = cmds;
	while (i != nb)
	{
		args[i++] = ft_strdup(tok->value);
		tok = tok->next;
	}
	args[nb] = NULL;
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
	}
	return (NULL);
}

/* LEAKS-LAND, LE ROYAUME DU LEAK ENTRE VOS MAINS :
char	*fill_tab(t_tok *node)
{
	char	*str;

	str = ft_strdup(node->key);
	str = ft_strjoin(str, "=");
	str = ft_strjoin(str, node->value);
	return (str);
}
*/

char	*fill_tab(t_tok *node)
{
	char *result;

	if (!node || !node->key || !node->value)
		return (NULL);
	result = malloc(strlen(node->key) + strlen(node->value));
	if (!result)
		return (NULL);
	ft_strcpy(result, node->key);
	ft_strlcat(result, "=", 0);
	ft_strlcat(result, node->value, 0);
	return (result);
}

char	**convert_envp(t_tok *head)
{
	t_tok	*node;
	char	**envp;
	int		count;
	int		i;

	count = 0;
	node = head;
	i = 0;
	while (node)
	{
		count++;
		node = node->next;
	}
	envp = malloc((count + 1) * sizeof(char *));
	node = head;
	while (node)
	{
		envp[i] = fill_tab(node);
		i++;
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
		printf("Error\n");
		//free(path);
		free_tab(args);
		exit(1);
	}
	free(path);
	free_tab(args);
}

void	execution_controller(t_tok *env, t_tok *tok_head)
{
	t_tok	*cmds;
	char	**envp;
	int		pid;

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
				pid = fork();
				if (pid == -1)
					return ;
				if (pid == 0)
					execute_cmd(env, envp, cmds);
				waitpid(pid, NULL, 0);
			}
		}
		cmds = cmds->next;
	}
	free_tab(envp);
}
