/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benjaminchabot <benjaminchabot@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 20:14:32 by rlaforge          #+#    #+#             */
/*   Updated: 2023/02/16 23:54:56 by benjamincha      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*test_relative_path(t_tok *env_tok, char *cmd)
{
	char	**env;
	char	*str;
	int		i;

	i = 0;
	env = ft_split(ft_getenv(env_tok, "PATH"), ':');
	while (env && env[i])
	{
		str = strjoin_pipex(env[i++], cmd);
		if (!access(str, X_OK))
		{
			free_tab(env);
			return (str);
		}
		free(str);
	}
	free_tab(env);
	return (NULL);
}

char	*c_to_str(char c)
{
	char	*str;

	str = malloc(sizeof(char) * 2);
	str[0] = c;
	str[1] = '\0';
	return (str);
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

char	*fill_tab(t_tok *node)
{
	char	*str;
	int		length;

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
