/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 15:25:27 by bchabot           #+#    #+#             */
/*   Updated: 2022/12/23 18:56:58 by rlaforge         ###   ########.fr       */
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
	args = malloc(sizeof(char*) * nb);
	while (i != nb)
	{
		tok = cmds;
		cmds = cmds->next;
		args[i++] = ft_strdup(tok->value);
	}
	return (args);
}

void	execute_cmd(t_tok *env, t_tok *cmds)
{
	char	**args;
	//char	*path;
	int		i;

	(void)env;
	args = get_cmd(cmds);
	i = 0;
	printf("[%d]: %s\n", i, args[i]);
	i++;
	while (args[i])
	{
		printf("[%d]: %s\n", i, args[i]);
		free(args[i++]);
	}
	free(args);

	//path = get_path(env);
	//if (!path || (execve(path, args, env)) == -1)
	//	printf ("Error\n");
}

void	execution_controller(t_tok *env, char *prompt)
{
	t_tok	*tok_head;
	t_tok	*cmds;

	tok_head = parsing_controller(prompt);
	cmds = tok_head;
	print_list(cmds);
	while (cmds)
	{
		if (*cmds->key == *K_CMD)
		{
			execute_builtins(env, cmds->value);
			execute_cmd(env, cmds);
		}
		cmds = cmds->next;
	}
	free(prompt);
	free_list(tok_head);
	return ;
}
