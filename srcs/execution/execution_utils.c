/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchabot <bchabot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 23:12:33 by benjamincha       #+#    #+#             */
/*   Updated: 2023/02/20 20:03:42 by bchabot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_path(t_tok *env_tok, char *cmd)
{
	char	*str;

	if (!cmd || !env_tok)
		return (NULL);
	if (cmd[0] == '/' || cmd[0] == '.')
	{
		str = ft_strdup(cmd);
		if (!access(str, X_OK) && is_regular_file(str))
			return (str);
		free(str);
		return (NULL);
	}
	else
		str = test_relative_path(env_tok, cmd);
	return (str);
}

int	nb_args(t_tok *cmds)
{
	t_tok	*tmp;
	int		nbr;

	tmp = cmds;
	nbr = 0;
	while (tmp && *tmp->key != '|')
	{
		if (*tmp->key == *K_CMD || *tmp->key == *K_ARG)
			nbr++;
		else if (*tmp->key == '>' || *tmp->key == '<' \
		|| ft_strcmp(tmp->key, ">>") == 0)
			tmp = tmp->next;
		tmp = tmp->next;
	}
	return (nbr);
}

char	**get_cmd(t_tok *cmds)
{
	char	**args;
	t_tok	*tok;
	int		nb;
	int		i;

	if (!cmds)
		return (NULL);
	tok = cmds;
	nb = nb_args(tok);
	i = 0;
	args = malloc(sizeof(char *) * (nb + 1));
	tok = cmds;
	while (i != nb)
	{
		if (*tok->key == *K_CMD || *tok->key == *K_ARG)
			args[i++] = ft_strdup(tok->value);
		else if (*tok->key == '>' || *tok->key == '<' \
		|| ft_strcmp(tok->key, ">>") == 0)
			tok = tok->next;
		tok = tok->next;
	}
	args[nb] = NULL;
	return (args);
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
	if (i == 0)
		no_cmd_msg(cmds->key, 127);
	return (i);
}

int	is_builtin(char *cmd)
{
	if (ft_strncmp(cmd, "echo", 5) == 0)
		return (2);
	if (ft_strncmp(cmd, "cd", 3) == 0)
		return (1);
	if (ft_strncmp(cmd, "pwd", 4) == 0)
		return (3);
	if (ft_strncmp(cmd, "export", 7) == 0)
		return (4);
	if (ft_strncmp(cmd, "unset", 6) == 0)
		return (5);
	if (ft_strncmp(cmd, "env", 4) == 0)
		return (6);
	if (ft_strncmp(cmd, "exit", 5) == 0)
		return (7);
	return (0);
}
