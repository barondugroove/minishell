/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchabot <bchabot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 15:25:27 by bchabot           #+#    #+#             */
/*   Updated: 2022/12/20 16:06:07 by bchabot          ###   ########.fr       */
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
	while (tmp)
	{
		if (ft_strncmp(tmp->key, "cmd", 4) == 0)
		{
			execute_builtins(env, tmp->value);
		}
		tmp = tmp->next;
	}
	return ;
}
