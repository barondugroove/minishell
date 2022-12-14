/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 17:36:49 by bchabot           #+#    #+#             */
/*   Updated: 2022/12/14 18:55:12 by rlaforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
/*
void	ft_lexer(char *prompt)
{
	char	*str;
	char	**cmd;
	int		i;
	t_tok	*tok_head;
	char	sep[] = {' ', '<', '>', '|'};

	tok_head = NULL;
	i = 0;
	//split sur les |, les cmd sont dans un tableau, ensuite on tokenize chaques cmd.
	cmd = ft_split(prompt, '|');
	while (cmd[i])
	{
		str = ft_strtok(cmd[i], sep);
		newnode(&tok_head, str, NULL);
		while (str)
		{
			str = ft_strtok(NULL, sep);
			newnode(&tok_head, str, NULL);
		}
		free(str);
		free(cmd[i++]);
	}
	free(cmd);
	print_list(&tok_head);
}*/


void	ft_lexer(char *prompt)
{
	char	*str;
	t_tok	*tok_head;
	char	sep[] = {'<', '>', '|'};

	tok_head = NULL;
	str = ft_strtok(prompt, sep);
	newnode(&tok_head, str, NULL);
	while (str)
	{
		str = ft_strtok(NULL, sep);
		newnode(&tok_head, str, NULL);
	}
	free(str);
	print_list(&tok_head);
}
