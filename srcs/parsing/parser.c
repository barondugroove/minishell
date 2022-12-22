/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 17:36:49 by bchabot           #+#    #+#             */
/*   Updated: 2022/12/22 18:05:21 by rlaforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	remove_quotes(t_tok *tok_head, char *str)
{
	int		len;
	int		start;
	char	quote;

	len = 0;
	start = 0;
	quote = '\0';
	while (str && str[len])
	{
		if ((str[len] == '"' || str[len] == '\'') && quote == '\0')
		{
			start = len;
			quote = str[len];
		}
		else if (str[len] == quote && quote != '\0')
		{
			quote = '\0';
			newtoken_back(&tok_head, ft_substr(str, start + 1, len - 1), \
				ft_strdup(K_DQUO));
			len++;
		}
		len++;
	}



	/*
	if (str[0] == '"')
		newtoken_back(&tok_head, ft_substr(str, 1, ft_strlen(str) - 2), \
		ft_strdup(K_DQUO));
	else if (str[0] == '\'')
		newtoken_back(&tok_head, ft_substr(str, 1, ft_strlen(str) - 2), \
		ft_strdup(K_QUO));
	*/
}

void	add_token(t_tok *tok_head, char *str)
{
	if (str[0] == '"' || str[0] == '\'')
		remove_quotes(tok_head, str);
	else if (ft_strchr(str, '|'))
		add_pipe_token(tok_head, str);
	else
		newtoken_back(&tok_head, ft_strdup(str), ft_strdup(K_ARG));
}

t_tok	*parser(char *prompt)
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
	return (tok_head);
}

// parse test| ls -la |grep "c'est trop cool" | wc -l | echo "voici un pipe : |"  mais il est entre '"' du coup il est pas pi|pe.
