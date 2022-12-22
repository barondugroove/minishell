/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchabot <bchabot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 12:36:07 by bchabot           #+#    #+#             */
/*   Updated: 2022/12/22 15:08:56 by bchabot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	minishell(char **envp)
{
	char	*prompt;
	t_tok	*env;

	env = init_env(envp);
	while (1)
	{
		prompt = readline("\033[0;34m🐚 Minishell \001\e[0m\002");
		if (!prompt)
			break ;
		else if (prompt[0] == '\0')
			continue ;
		else
		{
			add_history(prompt);
			execution(env, prompt);
		}
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
