/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 23:21:57 by benjamincha       #+#    #+#             */
/*   Updated: 2023/02/16 23:07:15 by rlaforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


void	print_list(t_tok *head)
{
	// ATTENTION, A PAS LAISSER
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

void	replace_tok_value(char **val, char *new_val)
{
	free(*val);
	*val = ft_strdup(new_val);
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
