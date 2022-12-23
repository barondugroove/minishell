/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 17:36:49 by bchabot           #+#    #+#             */
/*   Updated: 2022/12/23 17:21:01 by rlaforge         ###   ########.fr       */
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
	

// Retire les quotes du début et de la fin.
	if (str[0] == '"')
		newtoken_back(&tok_head, ft_substr(str, 1, ft_strlen(str) - 2), \
		ft_strdup(K_DQUO));
	else if (str[0] == '\'')
		newtoken_back(&tok_head, ft_substr(str, 1, ft_strlen(str) - 2), \
		ft_strdup(K_QUO));

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
            while (j < len - 1) {
                str[j] = str[j + 1];
                j++;
            }
            str[j] = '\0';
            len = strlen(str);
            i--;
        }
		else if (str[i] == quote && quote != '\0')
		{
			quote = '\0';
            j = i;
            while (j < len - 1) {
                str[j] = str[j + 1];
                j++;
            }
            str[j] = '\0';
            len = strlen(str);
            i--;
        }
        i++;
    }
	newtoken_back(&tok_head, ft_strdup(str), \
		ft_strdup(K_ARG));
}

void	add_token(t_tok *tok_head, char *str)
{
	if (ft_strchr(str, '"') || ft_strchr(str, '\''))
		remove_quotes(tok_head, str);
	else if (ft_strchr(str, '|'))
		add_pipe_token(tok_head, str);
	else
		newtoken_back(&tok_head, ft_strdup(str), ft_strdup(K_ARG));
}

t_tok	*parsing_controller(char *prompt)
{
	char	*str;
	t_tok	*tok_head;

	tok_head = NULL;
	str = tokenizer(prompt);
	if (str)
		newtoken_back(&tok_head, ft_strdup(str), ft_strdup(K_CMD));
	while (str)
	{
		str = tokenizer(NULL);
		if (str && *str == ERROR_CHAR)
		{
			printf("Error: quote not closed\n");
			free_list(tok_head);
			return (NULL);
		}
		if (str && *str)
			add_token(tok_head, str);
	}
	clean_token_list(tok_head);
	return (tok_head);
}

// parse test| ls -la |grep "c'est trop cool" | wc -l | e"c"ho "voici un pipe : |"  mais il est entre '"' du coup il est pas pi|pe.
