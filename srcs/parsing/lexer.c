/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 17:36:49 by bchabot           #+#    #+#             */
/*   Updated: 2022/12/21 19:20:08 by rlaforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_pipe_token(t_tok *tok_head, char *str)
{
	int	i;

	i = 0;
	if (str[ft_strlen(str) - 1] == '|')
	{
		newnode_back(&tok_head, ft_substr(str, 0, ft_strlen(str) - 1), K_ARG);
		newnode_back(&tok_head, ft_strdup("|"), K_PIPE);
	}
	else if (str[0] == '|')
	{
		newnode_back(&tok_head, ft_strdup("|"), K_PIPE);
		newnode_back(&tok_head, ft_substr(str, 1, ft_strlen(str)), K_ARG);
	}
	else
	{
		while (str[i] != '|')
			i++;
		newnode_back(&tok_head, ft_substr(str, 0, i), K_ARG);
		newnode_back(&tok_head, ft_strdup("|"), K_PIPE);
		newnode_back(&tok_head, ft_substr(str, i + 1, ft_strlen(str)), K_CMD);
	}
}

void	add_token(t_tok *tok_head, char *str)
{
	if (str[0] == '"' || str[0] == '\'')
	{
		if (str[0] == '"')
			newnode_back(&tok_head, ft_substr(str, 1, ft_strlen(str) - 2), \
			K_DQUO);
		else if (str[0] == '\'')
			newnode_back(&tok_head, ft_substr(str, 1, ft_strlen(str) - 2), \
			K_QUO);
	}
	else if (str[0] == '|' && !str[1])
		newnode_back(&tok_head, ft_strdup("|"), K_PIPE);
	else if (ft_strchr(str, '|'))
		add_pipe_token(tok_head, str);
	else
		newnode_back(&tok_head, ft_strdup(str), K_ARG);
}

t_tok	*ft_lexer(char *prompt)
{
	char	*str;
	t_tok	*tok_head;

	tok_head = NULL;
	str = tokenizer(prompt);
	if (str)
		newnode_back(&tok_head, ft_strdup(str), K_CMD);
	while (str)
	{
		str = tokenizer(NULL);
		if (str && *str == ERROR_CHAR)
		{
			printf("Error: quote not closed\n");
			free(prompt);
			return (NULL);
		}
		if (str && *str)
			add_token(tok_head, str);
	}
	free(str);
	free(prompt);
	return (tok_head);
}

// cd toto| ls -la |grep "c'est trop cool" | wc -l | echo "voici un pipe : |"  mais il est entre '"' du coup il est pas pi|pe.
