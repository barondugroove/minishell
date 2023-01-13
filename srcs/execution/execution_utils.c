/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 23:12:33 by benjamincha       #+#    #+#             */
/*   Updated: 2023/01/14 00:15:57 by rlaforge         ###   ########.fr       */
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
	while (tok && *tok->key != '|')
	{
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
	int	length;

	length = ft_strlen(node->key) + ft_strlen(node->value) + 2;
	str = malloc(sizeof(char) * length);
	if (!str)
		return (NULL);
	ft_strlcpy(str, node->key, length);
	ft_strlcat(str, "=", length);
	ft_strlcat(str, node->value, length);
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
	if (ft_strncmp(cmd, "echo", 4) == 0)
		return (1);
	if (ft_strncmp(cmd, "cd", 2) == 0)
		return (1);
	if (ft_strncmp(cmd, "pwd", 3) == 0)
		return (1);
	if (ft_strncmp(cmd, "export", 6) == 0)
		return (1);
	if (ft_strncmp(cmd, "unset", 5) == 0)
		return (1);
	if (ft_strncmp(cmd, "env", 3) == 0)
		return (1);
	return (0);
}