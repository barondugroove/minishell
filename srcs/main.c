/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchabot <bchabot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 12:36:07 by bchabot           #+#    #+#             */
/*   Updated: 2022/11/30 19:55:40 by bchabot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int ac, char **av, char **envp)
{
	char	*prompt;

	(void)ac;
	(void)av;
	(void)envp;
	while (1)
	{
		prompt = readline("\033[0;34m 🐚 minishell \001\e[0m\002");
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
	exit(EXIT_SUCCESS);
}
