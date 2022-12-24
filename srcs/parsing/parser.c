/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 17:36:49 by bchabot           #+#    #+#             */
/*   Updated: 2022/12/24 02:54:30 by rlaforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
void	remove_quotes(t_tok *tok_head, char *tok)
{
// Sépare les quotes.
	char	*str;
	char	*buf;

	buf = ft_strdup(tok);
	str = ft_strtok(buf, "\"'");
	while (str)
	{
		if (*str)
			newtoken_back(&tok_head, ft_strdup(str), \
				ft_strdup(K_DQUO));
		str = ft_strtok(NULL, "\"'");
	}
	free(buf);
}
*/

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


/*
void add_quote_token(t_tok *tok_head, char *str)
{
    char quote = '\0';
    int i = 0;
    int len = strlen(str);
    while (i < len)
    {
        if ((str[i] == '"' || str[i] == '\'') && quote == '\0')
        {
            quote = str[i];
            ft_memmove(str + i, str + i + 1, len - i);
            len--;
        }
        else if (str[i] == quote && quote != '\0')
        {
            quote = '\0';
            ft_memmove(str + i, str + i + 1, len - i);
            len--;
        }
        else
            i++;
    }
    newtoken_back(&tok_head, ft_strdup(str), ft_strdup(K_ARG));
}
*/

/*
void add_quote_token(t_tok *tok_head, char *str)
{
    char quote = '\0';
    int i = 0;
    int len = strlen(str);
    while (i < len)
    {
        if (str[i] == quote)
            quote = '\0';
        else if (str[i] == '"' || str[i] == '\'')
            quote = str[i];
        if (quote != '\0')
        {
            ft_memmove(str + i, str + i + 1, len - i);
            len--;
        }
        else
            i++;
    }
    newtoken_back(&tok_head, ft_strdup(str), ft_strdup(K_ARG));
}
*/


void add_quote_token(t_tok **tok_head, char *str)
{
    char quote = '\0';
    int i = 0;
    int len = strlen(str);
    while (i < len)
    {
        if ((str[i] == '"' || str[i] == '\'') && quote == '\0')
        {
            quote = str[i];
            ft_memmove(str + i, str + i + 1, len - i);
            len--;
        }
        else if (str[i] == quote && quote != '\0')
        {
            quote = '\0';
            ft_memmove(str + i, str + i + 1, len - i);
            len--;
        }
        else
            i++;
    }
    newtoken_back(tok_head, ft_strdup(str), ft_strdup(K_ARG));
}


/*
void	remove_quotes(t_tok *tok_head, char *str)
{
    int len;
    int i;
	int j;
	char	quote;

	quote = '\0';
	len = strlen(str);
	i = 0;
    while (i < len)
	{
        if ((str[i] == '"' || str[i] == '\'') && quote == '\0')
		{
			quote = str[i];	
            j = i;
            while (j < len - 1)
			{
                str[j] = str[j + 1];
                j++;
            }
            str[j] = '\0';
            len--;
        }
		else if (str[i] == quote && quote != '\0')
		{
			quote = '\0';
            j = i;
            while (j < len - 1)
			{
                str[j] = str[j + 1];
                j++;
            }
            str[j] = '\0';
            len--;
        }
		else
        	i++;
    }
	newtoken_back(&tok_head, ft_strdup(str), \
		ft_strdup(K_ARG));
}
*/

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

// parse test| ls -la |grep "c'est trop cool" | wc -l | e"c"'h'o "voici un pipe : |"  mais il est entre '"' du coup il est pas pi|pe.
