/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 20:14:32 by rlaforge          #+#    #+#             */
/*   Updated: 2022/12/29 01:45:28 by rlaforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

void	free_list(t_tok *head)
{
	t_tok	*tmp;

	tmp = head;
	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
	free(head);
}

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

char *c_to_str(char c)
{
    char *str;

    str = malloc(sizeof(char) * 2);
    str[0] = c;
    str[1] = '\0';
    return (str);
}