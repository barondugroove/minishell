/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchabot <bchabot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 17:36:49 by bchabot           #+#    #+#             */
/*   Updated: 2022/12/19 17:28:22 by bchabot          ###   ########.fr       */
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

void	add_pipe_token(t_tok *tok_head, char *str)
{
	int i;

	i = 0;
	if (str[ft_strlen(str) - 1] == '|')
	{
		newnode_back(&tok_head, ft_substr(str, 0, ft_strlen(str) - 1), "arg");
		newnode_back(&tok_head, ft_strdup("|"), "pipe");
	}
	else if (str[0] == '|')
	{
		newnode_back(&tok_head, ft_strdup("|"), "pipe");
		newnode_back(&tok_head, ft_substr(str, 1, ft_strlen(str)), "arg");
	}
	else
	{
		while (str[i] != '|')
			i++;
		newnode_back(&tok_head, ft_substr(str, 0, i ), "arg");
		newnode_back(&tok_head, ft_strdup("|"), "pipe");
		newnode_back(&tok_head, ft_substr(str, i + 1, ft_strlen(str)), "arg");
	}
}

void	add_token(t_tok *tok_head, char *str)
{
	if (str[0] == '"' || str[0] == '\'')
	{
		if (str[0] == '"')
			newnode_back(&tok_head, ft_substr(str, 1, ft_strlen(str) - 2), "dquote");
		else if (str[0] == '\'')
			newnode_back(&tok_head, ft_substr(str, 1, ft_strlen(str) - 2), "quote");
	}
	else if (str[0] == '|' && !str[1])
		newnode_back(&tok_head, ft_strdup("|"), "pipe");
	else if (ft_strchr(str, '|'))
		add_pipe_token(tok_head, str);
	else
		newnode_back(&tok_head, str, "arg");
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
		if (str && *str == ERROR_CHAR)
		{
			printf("Error: quote not closed\n");
			free(prompt);
			return ;
		}
		if (str && *str)
			add_token(tok_head, str);
	}
	free(str);
	free(prompt);
	print_list(tok_head);
	//free_list(tok_head);
}

// cd toto| ls -la |grep "c'est trop cool" | wc -l | echo "voici un pipe : |"  mais il est entre '"' du coup il est pas pi|pe.
