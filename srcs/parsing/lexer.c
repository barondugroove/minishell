/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 17:36:49 by bchabot           #+#    #+#             */
/*   Updated: 2022/12/17 14:31:24 by rlaforge         ###   ########.fr       */
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
		free(cmd[i++]);
	}
	free(cmd);
	print_list(&tok_head);
	//clear_list(&tok_head);
}




/* Only tokenizer but chelou
void	ft_lexer(char *prompt)
{
	char *token;
	char *copy;
	//char *token_copy;
	t_tok	*tok_head;

	copy = strdup(prompt);
	tok_head = NULL;
	// Découper la chaîne en utilisant " " comme délimiteur
	token = tokenizer(copy, "|");
	while (token) {
		token_copy = ft_strdup(token);
		char *subtoken = tokenizer(NULL, " 	");
		while (subtoken)
		{
			newnode(&tok_head, ft_strdup(subtoken), "arg");
			subtoken = tokenizer(NULL, " 	");
		}
		free(token_copy);
		token = tokenizer(NULL, "|");
	}
	free(copy);

	print_list(&tok_head);
}
*/



/* Only tokenizer but loosing static when tokenizing cmd
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