/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 12:36:07 by bchabot           #+#    #+#             */
/*   Updated: 2023/01/09 16:40:06 by rlaforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	minishell(char **envp)
{
	char	*prompt;
	t_tok	*cmds;
	t_tok	*env;

	env = init_env(envp);
	while (1)
	{
		prompt = readline("\033[0;34m🐚 Minishell \e[0m");
		if (!prompt)
		{
			printf("exit\n");
			break ;
		}
		else if (prompt[0] == '\0')
			continue ;
		else
		{
			add_history(prompt);
			cmds = parsing_controller(env, prompt);
			execution_controller(env, cmds);
			free_list(cmds);
		}
		free(prompt);
	}
	free_list(env);
}

int	main(int ac, char **av, char **envp)
{
	(void)av;
	if (ac != 1)
		return (1);
	minishell(envp);
	return (0);
}

//valgrind --suppressions=.vsupp --leak-check=full --show-leak-kinds=all ./minishell
