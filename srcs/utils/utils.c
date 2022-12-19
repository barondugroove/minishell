/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 20:14:32 by rlaforge          #+#    #+#             */
/*   Updated: 2022/12/18 20:52:11 by rlaforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"




void	print_list(t_tok *head)
{
	t_tok	*tok;

	tok = head;
	while (tok)
	{
		printf("%s$  %s\n", tok->value, tok->key);
		tok = tok->next;
	}
}

void	free_list(t_tok *head)
{
	while (head)
	{
		printf("%s$ LOL  %s\n", head->value, head->key);
		free(head->value);
		free(head);
		head = head->next;
	}
}

t_tok	*newnode(char *data, char *key)
{
	t_tok	*tok;

	tok = malloc(sizeof(t_tok));
	if (tok)
	{
		tok->value = ft_strdup(data);
		tok->key = key;
		tok->next = NULL;
	}
	return (tok);
}

void	newnode_back(t_tok **head, char *data, char *key)
{
	t_tok	*tok;
	t_tok	*tmp;

	tok = newnode(data, key);
	if (!*head || !head)
	{
		*head = tok;
		return ;
	}
	tmp = *head;
	while (tmp && tmp->next)
		tmp = tmp->next;
	tmp->next = tok;
}
