/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 17:36:49 by bchabot           #+#    #+#             */
/*   Updated: 2022/12/16 15:26:43 by rlaforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_lexer(char *prompt)
{
	char	*str;
	char	**cmd;
	int		i;
	t_tok	*tok_head;

	tok_head = NULL;
	i = 0;
	//split sur les |, les cmd sont dans un tableau, ensuite on tokenize chaques cmd.
	cmd = ft_split(prompt, '|');
	while (cmd[i])
	{
		if (i >= 1)
			newnode(&tok_head, "|", "pipe");
		str = tokenizer(cmd[i], " 	");
		newnode(&tok_head, str, "cmd");
		while (str)
		{
			str = tokenizer(NULL, " 	");
			if (str)
				newnode(&tok_head, str, "arg");
		}
		i++;
	}
	print_list(&tok_head);
}





/*
void	ft_lexer(char *prompt)
{
	char	*str;
	char	*cmd;
	t_tok	*tok_head;

	tok_head = NULL;
	cmd = tokenizer(prompt, "<>|");
	while (cmd)
	{
		str = tokenizer(cmd, " 	");
		newnode(&tok_head, str, "cmd");
		while (str)
		{
			str = tokenizer(NULL, " 	");
			newnode(&tok_head, str, "arg");
		}
		cmd = tokenizer(prompt, "<>|");
	}
	print_list(&tok_head);
}
*/