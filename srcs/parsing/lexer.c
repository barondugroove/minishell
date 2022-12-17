/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 17:36:49 by bchabot           #+#    #+#             */
/*   Updated: 2022/12/17 16:10:02 by rlaforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	clean_list(t_tok **head)
{
	t_tok	*tok;
	char	*buf;

	tok = *head;
	while (tok)
	{
		if (tok->value[0] == '|')
		{
			tok->key = "pipe";
			tok = tok->next;
			tok->key = "cmd";
		}
		else if (tok->value[0] == '"' || tok->value[0] == '\'')
		{
			if (tok->value[0] == '"')
				tok->key = "dquote";
			else if (tok->value[0] == '\'')
				tok->key = "quote";
			buf = ft_substr(tok->value, 1, ft_strlen(tok->value) - 2);
			free (tok->value);
			tok->value = ft_strdup(buf);
			free (buf);
		}
		else
			tok->key = "arg";
		tok = tok->next;
	}
}


void	ft_lexer(char *prompt)
{
	char	*str;
	t_tok	*tok_head;

	tok_head = NULL;
	str = tokenizer(prompt);
	newnode(&tok_head, str, "cmd");
	while (str)
	{
		str = tokenizer(NULL);
		if (str)
			newnode(&tok_head, str, NULL);
	}
	printf("\nLIST DIRTY :\n\n");
	print_list(&tok_head);

	clean_list(&tok_head);

	printf("\nLIST CLEAN :\n\n");
	print_list(&tok_head);
}

// cd toto| ls -la |grep "c'est trop cool" | wc -l | echo "voici un pipe : |"  mais il est entre '"' du coup il est pas pipe.