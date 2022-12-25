/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 17:36:49 by bchabot           #+#    #+#             */
/*   Updated: 2022/12/24 18:23:25 by rlaforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


void	clean_token_list(t_tok *head)
{
	t_tok	*tok;

	tok = head;
	while (tok)
	{
		if(*tok->key == '|')
		{
			free(tok->next->key);
			tok->next->key = ft_strdup("C");
		}
		tok = tok->next;
	}
}

void	add_token(t_tok **tok_head, char *str)
{
	if (ft_strchr(str, '"') || ft_strchr(str, '\''))
		add_quote_token(tok_head, str);
	else if (ft_strchr(str, '|'))
		add_pipe_token(tok_head, str);
	else
		newtoken_back(tok_head, ft_strdup(str), ft_strdup(K_ARG));
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
			printf("Parsing error: consecutive pipe\n");
			free_list(tok_head);
			return (NULL);
		}
		str = tokenizer(NULL);
	}
	clean_token_list(tok_head);
	return (tok_head);
}

// e"c"'h'o "parse test"| ls -la |grep "c'est trop cool" | wc -l | "voici un pipe : |"  mais il est entre '"' du coup il est pas pi|pe.
// e"c"'h'o |"parse test" ls -la |grep| "c'est trop cool"| wc -l | "voici un pipe : |"  mais il est entre '"' du coup il est pas pi|pe.