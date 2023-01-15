/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benjaminchabot <benjaminchabot@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 23:12:33 by benjamincha       #+#    #+#             */
/*   Updated: 2023/01/14 22:58:29 by benjamincha      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

int	is_builtin(char *cmd)
{
	char	*builtins[] = {"echo", "cd", "pwd", "export", "unset", "env", NULL};
	int		i;

	i = 0;
	while (builtins[i])
	{
		if (ft_strncmp(cmd, builtins[i], ft_strlen(builtins[i])) == 0)
			return (1);
		i++;
	}
	return (0);
}