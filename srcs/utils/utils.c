/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 20:14:32 by rlaforge          #+#    #+#             */
/*   Updated: 2022/12/08 20:14:46 by rlaforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_list(t_tok **head)
{
	t_tok	*tok;

	tok = *head;
	while (tok)
	{
		if (tok->value)
			printf("%s\n", tok->value);
		tok = tok->next;
	}
}

void	newnode(t_tok **head, char *data, char *key)
{
	t_tok	*tok;
	t_tok	*tmp;

	tok = malloc(sizeof(t_tok));
	if (tok)
	{
		tok->value = data;
		tok->key = key;
		tok->next = NULL;
	}
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
