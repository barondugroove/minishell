/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchabot <bchabot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 12:36:07 by bchabot           #+#    #+#             */
/*   Updated: 2023/02/23 19:44:19 by bchabot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_exit_code = 0;

void	minishell(char **envp)
{
	char	*prompt;
	t_tok	*cmds;
	t_tok	*env;

	env = init_env(envp);
	while (1)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, ctrl_c_handler);
		prompt = readline("\033[0;34m🐚 Minishell \e[0m");
		if (!prompt)
			break ;
		else if (prompt[0] != '\0')
		{
			add_history(prompt);
			cmds = parsing_controller(env, &prompt);
			execution_controller(env, cmds, &prompt);
			free_list(cmds);
		}
		free(prompt);
	}
	free_list(env);
	printf("exit\n");
}

int	main(int ac, char **av, char **envp)
{
	(void)av;
	if (ac != 1)
		return (1);
	minishell(envp);
	return (0);
}
