/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_quote_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 17:57:55 by rlaforge          #+#    #+#             */
/*   Updated: 2022/12/24 17:57:55 by rlaforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* Tokenuize et sépare les quotes.
void	remove_quotes(t_tok *tok_head, char *tok)
{
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

/* WORK CHELOU
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

/* NO PIPE CHECK
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

int	pipe_error(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '|' && str[i + 1] == '|' && str[i + 2] == '|')
		{
			*str = ERROR_CHAR;
			return (1);
		}
		i++;
	}
	return (0);
}

void    clean_token(t_tok **tok_head, char *str)
{
    char quote;
    int i;
    int len;

    quote = '\0';
    len = ft_strlen(str);
    i = 0;
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
        else if  (str[i] == '|' && quote == '\0')
        {
            newtoken_back(tok_head, ft_substr(str, 0, i), ft_strdup(K_ARG));
            newtoken_back(tok_head, ft_strdup("|"), ft_strdup(K_PIPE));
            ft_memmove(str, str + i + 1, len - i);
            i = 0;
            len = ft_strlen(str);
        }
        else if  (str[i] == '<' && quote == '\0')
        {
            newtoken_back(tok_head, ft_substr(str, 0, i), ft_strdup(K_ARG));
            newtoken_back(tok_head, ft_strdup("<"), ft_strdup(K_REDIR));
            ft_memmove(str, str + i + 1, len - i);
            i = 0;
            len = ft_strlen(str);
        }
        else if  (str[i] == '>' && quote == '\0')
        {
            newtoken_back(tok_head, ft_substr(str, 0, i), ft_strdup(K_ARG));
            newtoken_back(tok_head, ft_strdup(">"), ft_strdup(K_REDIR));
            ft_memmove(str, str + i + 1, len - i);
            i = 0;
            len = ft_strlen(str);
        }
        else
            i++;
    }
}

void	add_token(t_tok **tok_head, char *str)
{
    
	if (ft_strchr(str, '"') || ft_strchr(str, '\'') || ft_strchr(str, '|') || ft_strchr(str, '<') || ft_strchr(str, '>'))
    {
        if (pipe_error(str))
            return ;
        while (str[0] == '|')
        {
            newtoken_back(tok_head, ft_strdup("|"), ft_strdup(K_PIPE));
            ft_memmove(str, str + 1, ft_strlen(str));
        }
        while (str[0] == '<')
        {
            printf("SUPER\n");
            newtoken_back(tok_head, ft_strdup("<"), ft_strdup(K_REDIR));
            ft_memmove(str, str + 1, ft_strlen(str));
        }
        while (str[0] == '>')
        {
            printf("SUPER\n");
            newtoken_back(tok_head, ft_strdup(">"), ft_strdup(K_REDIR));
            ft_memmove(str, str + 1, ft_strlen(str));
        }
        clean_token(tok_head, str);
    }
    if (*str)
        newtoken_back(tok_head, ft_strdup(str), ft_strdup(K_ARG));
}
