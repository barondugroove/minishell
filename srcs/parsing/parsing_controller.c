/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_controller.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 17:36:49 by bchabot           #+#    #+#             */
/*   Updated: 2022/12/25 15:45:39 by rlaforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


int	clean_token_list(t_tok *head)
{
	t_tok	*tok;

	tok = head;

	if (*tok->key == '|')
		return (1);
	free(tok->key);
	tok->key = ft_strdup("C");
	while (tok)
	{
		if(*tok->key == '|')
		{
			if (!tok->next)
				return (1);
			free(tok->next->key);
			tok->next->key = ft_strdup("C");
		}
		tok = tok->next;
	}
	return (0);
}

t_tok	*parsing_controller(char *prompt)
{
	char	*str;
	t_tok	*tok_head;

	tok_head = NULL;
	str = tokenizer(prompt);
	while (str)
	{
		if (str && *str == ERROR_CHAR)
		{
			printf("Parsing error: quote not closed\n");
			free_list(tok_head);
			return (NULL);
		}
		if (str && *str)
			add_token(&tok_head, str);
		if (str && *str == ERROR_CHAR)
		{
			printf("Parsing error: plein de pipe a la suite, t'es fou ou quoi???\n");
			free_list(tok_head);
			return (NULL);
		}
		str = tokenizer(NULL);
	}
	if(clean_token_list(tok_head))
	{
		printf("Parsing error: pipe a une extremitée du prompt, tu veux que je pipe comment avec ça moi?????\n");
		free_list(tok_head);
		return (NULL);
	}
	return (tok_head);
}

// e"c"'h'o "parse test"| ls -la |grep "c'est trop cool" | wc -l | "voici un pipe : |"  mais il est entre '"' du coup il est pas pi|pe.
// e"c"'h'o |"parse test" ls -la |grep| "c'est trop cool"| wc -l | "voici un pipe : |"  mais il est entre '"' du coup il est pas pi|pe.

// 'e'"c"''"ho"|ls|w'c'