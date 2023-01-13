/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_controller.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 17:36:49 by bchabot           #+#    #+#             */
/*   Updated: 2023/01/14 00:25:24 by rlaforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void replace_var_env(t_tok *env, t_tok *tok)
{
	char *avant;
	char *apres;
	char *buf;

	if (tok->value[0] == '$' && tok->value[1] == '?' && !tok->value[2])
	{
		free(tok->value);
		tok->value = ft_strdup(ft_itoa(exit_code));
		return ;
	}
	avant = ft_strtok(tok->value, "$");
	apres = ft_strtok(NULL, "\0");
	if (!apres)
	{
		buf = ft_getenv(env, avant);
		free(tok->value);
		tok->value = ft_strdup(buf);
	}
	else
	{
		apres = ft_getenv(env, apres);
		buf = ft_strjoin(avant, apres);
		free(tok->value);
		tok->value = ft_strdup(buf);
		free(buf);
	}
}

int	clean_token_list(t_tok *env, t_tok *head)
{
	t_tok	*tok;

	tok = head;

	if (*tok->key == '|')
		return (1);
	free(tok->key);
	tok->key = ft_strdup("C");
	while (tok)
	{
		if (*tok->key == '|')
		{
			if (!tok->next)
				return (1);
			free(tok->next->key);
			tok->next->key = ft_strdup("C");
		}
		if (ft_strchr(tok->value, '$'))
			replace_var_env(env, tok);
		tok = tok->next;
	}
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
			free_list(tok_head);
			return (NULL);
		}
		if (str && *str)
			add_token(&tok_head, str);
		if (str && *str == ERROR_CHAR)
		{
			printf("syntax error near unexpected token '|'\n");
			exit_code = 2;
			free_list(tok_head);
			return (NULL);
		}
		str = tokenizer(NULL);
	}
	if(clean_token_list(env, tok_head))
	{
		printf("syntax error near unexpected token '|'\n");
		exit_code = 2;
		free_list(tok_head);
		return (NULL);
	}
	return (tok_head);
}

// e"c"'h'o "parse test"| ls -la |grep "c'est trop cool" | wc -l | "voici un pipe : |"  mais il est entre '"' du coup il est pas pi|pe.
// e"c"'h'o |"parse test" ls -la |grep| "c'est trop cool"| wc -l | "voici un pipe : |"  mais il est entre '"' du coup il est pas pi|pe.

// 'e'"c"''"ho"|ls|w'c'