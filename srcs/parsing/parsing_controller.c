/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_controller.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benjaminchabot <benjaminchabot@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 17:36:49 by bchabot           #+#    #+#             */
/*   Updated: 2023/02/16 02:17:58 by benjamincha      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// APRES LA REDIR C TOUJOURS UN FILE WALLAH
// ET SI JAI UNE REDIR AU DEBUT, IL YA PLUS DE COMMANDE DU TOUT :(
// GENRE <Makefile cat
// PAS COOL

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

int	check_redir_error(t_tok *tok)
{
	t_tok	*buf;

	if (tok->next && tok->next->next
		&& (*tok->key == '<' || *tok->key == '>')
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
			free(tok->key);
			if (*tok->next->key == '>')
				tok->key = ft_strdup(">>");
			else
				tok->key = ft_strdup("<<");
			buf = tok->next;
			tok->next = tok->next->next;
			free(buf->key);
			free(buf->value);
			free(buf);
		}
	}
	return (0);
}

int	clean_token_list(t_tok *head, t_tok *env)
{
	t_tok	*tok;
	char	*str;

	tok = head;
	if (*tok->key == '|')
		return (1);
	if (*tok->key != '<' && *tok->key != '>')
	{
		free(tok->key);
		tok->key = ft_strdup("C");
	}
	while (tok)
	{
		str = get_path(env, tok->value);
		if (str && is_regular_file(str))
		{
			free(str);
			free(tok->key);
			tok->key = ft_strdup("C");
		}
		if (check_redir_error(tok))
			return (1);
		// if ((*tok->key == '<' || *tok->key == '>') && tok->next)
		// {
		// 	free(tok->next->key);
		// 	tok->next->key = ft_strdup("F");
		// 	tok = tok->next;
		// }
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
	return (0);
}


//ec"h"o "$USER"os l"'"encule et son '$HOME' c"'"est $HOME

void	cat_var_to_prompt(char **prompt, char *ptr, char *value, char *end)
{
	char	*str;
	
	str = malloc(sizeof(char) * (ft_strlen(*prompt)
				+ ft_strlen(value) + ft_strlen(end) + 1));
	str[ft_strlen(*prompt) + ft_strlen(value) + ft_strlen(end)] = '\0';
	ft_strlcpy(str, *prompt, ptr - *prompt + 1);
	if (value)
		ft_strcat(str, value);
	ft_strcat(str, end);
	free(*prompt);
	*prompt = str;
}

void	replace_var_env(t_tok *env, char **prompt, char *ptr)
{
	char	*end;
	char	*value;
	char	*var;
	int		varlen;

	end = ptr;
	varlen = 0;
	while (*end != '"' && *end != ' ' && *end != '\0' && end++)
		varlen++;
	var = malloc(sizeof(char) * (varlen + 1));
	ft_strlcpy(var, end - varlen, varlen + 1);
	if (*(var + 1) && *(var + 1) == '?')
	{
		value = ft_itoa(g_exit_code);
		end = var + 2;
	}
	else
		value = ft_getenv(env, var + 1);
	free(var);
	cat_var_to_prompt(prompt, ptr, value, end);
}

void	check_var_env(t_tok *env, char **prompt)
{
	char	*ptr;
	char	quote;

	quote = '\0';
	ptr = *prompt;
	while (*ptr)
	{
		if (*ptr == '$' && *(ptr + 1) && *(ptr + 1) != '"'
			&& *(ptr + 1) != ' ' && *(ptr + 1) != '$'
			&& quote != '\'')
		{
			replace_var_env(env, prompt, ptr);
			ptr = *prompt;
			quote = '\0';
		}
		else if (quote == '\0' && (*ptr == '"' || *ptr == '\''))
			quote = *ptr;
		else if (*ptr == quote && quote != '\0')
			quote = '\0';
		ptr++;
	}
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
			printf("Parsing error: quote not closed\n");
			g_exit_code = 2;
			free_list(tok_head);
			return (NULL);
		}
		add_token(&tok_head, str);
		str = tokenizer(NULL);
	}
	if (clean_token_list(tok_head, env))
	{
		printf("syntax error\n");
		g_exit_code = 2;
		free_list(tok_head);
		return (NULL);
	}
	return (tok_head);
}
