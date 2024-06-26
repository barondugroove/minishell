/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_controller.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 17:36:49 by bchabot           #+#    #+#             */
/*   Updated: 2023/02/23 20:00:08 by rlaforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_redir_error(t_tok *tok)
{
	if (tok->next && tok->next->next && (*tok->key == '<' || *tok->key == '>')
		&& (*tok->next->key == '<' || *tok->next->key == '>')
		&& (*tok->next->next->key == '<' || *tok->next->next->key == '>'))
		return (1);
	if (tok->next && ((*tok->key == '<' && *tok->next->key == '>')
			|| (*tok->key == '>' && *tok->next->key == '<')))
		return (1);
	if (*tok->key == '<' || *tok->key == '>')
	{
		if (tok->next && *tok->next->key == *tok->key)
		{
			if (*tok->next->key == '>')
				replace_tok_value(&tok->key, ">>");
			else
				replace_tok_value(&tok->key, "<<");
			remove_node(&tok, tok->next);
		}
	}
	if (((*tok->key == '<' || *tok->key == '>')
			&& (!tok->next || *tok->next->key == '|')))
		return (1);
	return (0);
}

void	is_tok_cmd(t_tok *tok, t_tok *env)
{
	char	*str;

	str = get_path(env, tok->value);
	if (str && is_regular_file(str))
	{
		free(str);
		replace_tok_value(&tok->key, "C");
	}
}

int	clean_token_list(t_tok *head, t_tok *env)
{
	t_tok	*tok;

	tok = head;
	if (tok && *tok->key == '|')
		return (1);
	if (tok && *tok->key != '<' && *tok->key != '>')
		replace_tok_value(&tok->key, "C");
	while (tok)
	{
		is_tok_cmd(tok, env);
		if (check_redir_error(tok))
			return (1);
		else if ((!check_redir_error(tok)
				&& (*tok->key == '<' || *tok->key == '>')) && tok->next)
			replace_tok_value(&tok->next->key, "A");
		if (*tok->key == '|')
		{
			if (!tok->next || *tok->next->key == '|')
				return (1);
			else if (*tok->next->key == 'A')
				replace_tok_value(&tok->next->key, "C");
		}
		tok = tok->next;
	}
	return (0);
}

void	parsing_error_msg(t_tok	*tok_head, char *str)
{
	printf("%s\n", str);
	g_exit_code = 2;
	free_list(tok_head);
}

t_tok	*parsing_controller(t_tok *env, char **prompt)
{
	t_tok	*tok_head;
	char	*str;

	check_var_env(env, prompt);
	tok_head = NULL;
	str = tokenizer(*prompt);
	if (!str)
		return (NULL);
	while (str)
	{
		if (*str == ERROR_CHAR)
		{
			parsing_error_msg(tok_head, \
			"minishell : parsing error: quote not closed");
			return (NULL);
		}
		add_token(&tok_head, str);
		str = tokenizer(NULL);
	}
	if (clean_token_list(tok_head, env))
	{
		parsing_error_msg(tok_head, "minishell : syntax error");
		return (NULL);
	}
	return (tok_head);
}
