/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchabot <bchabot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 15:25:27 by bchabot           #+#    #+#             */
/*   Updated: 2022/12/21 19:32:11 by bchabot          ###   ########.fr       */
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

void	exec(t_tok *env, char *prompt)
{
	t_tok	*cmds;
	t_tok	*tmp;

	cmds = ft_lexer(prompt);
	tmp = cmds;
	//print_list(tmp);
	while (tmp)
	{
		if (*tmp->key == *K_CMD)
			execute_builtins(env, tmp->value);
		tmp = tmp->next;
	}
	free_list(cmds);
	return ;
}
