/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 12:36:07 by bchabot           #+#    #+#             */
/*   Updated: 2022/12/16 13:30:44 by rlaforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	minishell(char **envp)
{
	char	*prompt;

	//init_env(envp);
	(void)envp;
	while (1)
	{
		prompt = readline("\033[0;34m🐚 Minishell \001\e[0m\002");
		if (!prompt)
			exit(EXIT_SUCCESS);
		else if (prompt[0] == '\0' || ft_strncmp(prompt, "\n", 1) == 0)
		{
			free(prompt);
			continue ;
		}
		else if (ft_strncmp(prompt, "exit", 4) == 0)
		{
			printf("%s\n", prompt);
			free(prompt);
			break ;
		}
		else
			ft_lexer(prompt);
		free(prompt);
	}
}

int	main(int ac, char **av, char **envp)
{
	(void)av;
	if (ac != 1)
		return (1);
	minishell(envp);
	return (0);
}
