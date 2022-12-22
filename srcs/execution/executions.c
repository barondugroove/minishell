/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 15:25:27 by bchabot           #+#    #+#             */
/*   Updated: 2022/12/22 01:15:22 by rlaforge         ###   ########.fr       */
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

void	execute_cmd(t_tok *env, t_tok *cmds)
{
	execute_builtins(env, cmds->value);
	//Execve avec les args dans cmds
	
}

void	execution(t_tok *env, char *prompt)
{
	t_tok	*tok_head;
	t_tok	*cmds;

	tok_head = parser(prompt);
	cmds = tok_head;
	print_list(cmds);
	while (cmds)
	{
		if (*cmds->key == *K_CMD)
			execute_cmd(env, tok_head);
		cmds = cmds->next;
	}
	free(prompt);
	free_list(tok_head);
	return ;
}
