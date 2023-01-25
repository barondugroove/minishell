/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 20:14:32 by rlaforge          #+#    #+#             */
/*   Updated: 2023/01/25 14:49:45 by rlaforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_tok	*newtoken(char *data, char *key)
{
	t_tok	*tok;

	tok = malloc(sizeof(t_tok));
	if (tok)
	{
		tok->value = data;
		tok->key = key;
		tok->next = NULL;
	}
	return (tok);
}

void	newtoken_back(t_tok **head, char *data, char *key)
{
	t_tok	*tok;
	t_tok	*tmp;

	tok = newtoken(data, key);
	if (!head || !*head)
	{
		*head = tok;
		return ;
	}
	tmp = *head;
	while (tmp && tmp->next)
		tmp = tmp->next;
	tmp->next = tok;
}

char	*c_to_str(char c)
{
	char	*str;

	str = malloc(sizeof(char) * 2);
	str[0] = c;
	str[1] = '\0';
	return (str);
}

char	*strjoin_pipex(char *s1, char *s2)
{
	char	*str;
	int		length;

	if (!s1 || !s2)
		return (NULL);
	length = ft_strlen(s1) + ft_strlen(s2) + 2;
	str = malloc(sizeof(char) * length);
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1, length);
	ft_strlcat(str, "/", length);
	ft_strlcat(str, s2, length);
	return (str);
}

/*
void	print_list(t_tok *head)
{
	t_tok	*tok;

	tok = head;
	printf("PRINTLIST:\n");
	while (tok)
	{
		printf("%s: %s$\n", tok->key, tok->value);
		tok = tok->next;
	}
}
*/