/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 17:36:49 by bchabot           #+#    #+#             */
/*   Updated: 2022/12/18 15:27:40 by rlaforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	clean_tokens(t_tok **head)
{
	t_tok	*tok;
	t_tok	*tok_buf;
	char	*buf;

	tok = *head;
	while (tok)
	{
		if (tok->value[0] == '|' && !tok->value[1])
		{
			tok->key = "pipe";
			tok = tok->next;
			tok->key = "cmd";
		}
		if (ft_strchr(tok->value, '|'))
		{
			tok->key = "pipe";
			if (!tok->value[1])
			{	
				tok = tok->next;
				tok->key = "cmd";
			}
			else if (tok->value[ft_strlen(tok->value) - 1] == '|')
			{
				buf = tok->value;
				free (tok->value);
				tok->value = ft_substr(buf, 0, ft_strlen(buf) - 2);
				tok->key = "arg";
				tok_buf = tok->next;
				tok->next = newnode(ft_strdup("|"), "pipe");
				tok = tok->next;
				tok->next = tok_buf;
				free (buf);
			}
			/*
			else if (tok->value[1])
			{
				buf = ft_substr(tok->value, 1, ft_strlen(tok->value));
				free (tok->value);
				tok->value = ft_strdup("|");
				tok_buf = tok->next;
				tok->next = newnode(ft_strdup(buf), "cmd");
				tok = tok->next;
				tok->next = tok_buf;
				free (buf);
			}*/
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
	newnode_back(&tok_head, str, "cmd");
	while (str)
	{
		str = tokenizer(NULL);
		if (str && *str)
			newnode_back(&tok_head, str, NULL);
	}
	printf("\nLIST DIRTY :\n\n");
	print_list(&tok_head);

	clean_tokens(&tok_head);

	printf("\nLIST CLEAN :\n\n");
	print_list(&tok_head);
}

// cd toto| ls -la |grep "c'est trop cool" | wc -l | echo "voici un pipe : |"  mais il est entre '"' du coup il est pas pi|pe.