/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_controller.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 17:36:49 by bchabot           #+#    #+#             */
/*   Updated: 2023/01/26 15:59:35 by rlaforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_list(t_tok *head)
{
	t_tok	*tok;

	tok = head;
	printf("Printlist:\n");
	while (tok)
	{
		printf("%s: %s$\n", tok->key, tok->value);
		tok = tok->next;
	}
	printf("Output:\n");
}

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

		// REDIR ERRORS VVV
		if (tok->next && tok->next->next
			&& (*tok->key == '<' || *tok->key == '>')
				&& (*tok->next->key == '<' || *tok->next->key == '>')
					&& (*tok->next->next->key == '<' || *tok->next->next->key == '>'))
				return (1);
		if (tok->next && ((*tok->key == '<' && *tok->next->key == '>') || (*tok->key == '>' && *tok->next->key == '<')))
			return (1);
		// REDIR ERRORS ^^^

		if (*tok->key == '<' || *tok->key == '>')
		{
			if (tok->next && *tok->next->key == *tok->key)
			{
				printf("\nDOUBLE REDIR\n\n");
				free(tok->key);
				if (*tok->next->key == '>')
					tok->key = ft_strdup(">>");
				else
					tok->key = ft_strdup("<<");
				t_tok	*buf;
				buf = tok->next;
				tok->next = tok->next->next;
				free(buf->key);
				free(buf->value);
				free(buf);
			}
		}
		if (*tok->key == '|')
		{
			if (!tok->next)
				return (1);
			else if (*tok->next->key == 'A')
			{
				free(tok->next->key);
				tok->next->key = ft_strdup("C");
			}
		}
		tok = tok->next;
	}
	print_list(head);
	return (0);
}

t_tok	*parsing_controller(t_tok *env, char *prompt)
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
			g_exit_code = 2;
			free_list(tok_head);
			return (NULL);
		}
		if (str && *str)
			add_token(env, &tok_head, str);
		str = tokenizer(NULL);
	}
	if (clean_token_list(tok_head))
	{
		printf("syntax error\n");
		g_exit_code = 2;
		free_list(tok_head);
		return (NULL);
	}
	return (tok_head);
}

// e"c"'h'o "parse test"| ls -la |grep "c'est trop cool" | wc -l | "voici un pipe : |"  mais il est entre '"' du coup il est pas pi|pe.
// e"c"'h'o |"parse test" ls -la |grep| "c'est trop cool"| wc -l | "voici un pipe : |"  mais il est entre '"' du coup il est pas pi|pe.

// 'e'"c"''"ho"|ls|w'c'