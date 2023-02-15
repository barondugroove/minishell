/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchabot <bchabot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 12:36:07 by bchabot           #+#    #+#             */
/*   Updated: 2023/02/14 15:58:38 by bchabot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_exit_code = 0;

void	child_c_handler(int sig)
{
	(void)sig;
	g_exit_code = 130;
	printf("\n");
}

void	ctrl_c_handler(int sig)
{
	(void)sig;
	g_exit_code = 130;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

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
		{
			printf("exit\n");
			break ;
		}
		else if (prompt[0] == '\0')
		{
			free(prompt);
			continue ;
		}
		else
		{
			add_history(prompt);
			cmds = parsing_controller(env, &prompt);
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

//valgrind --suppressions=.vsupp --leak-check=full --show-leak-kinds=all --trace-children=yes ./minishell
