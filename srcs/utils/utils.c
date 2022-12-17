/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 20:14:32 by rlaforge          #+#    #+#             */
/*   Updated: 2022/12/17 14:23:27 by rlaforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_list(t_tok **head)
{
	t_tok	*tok;

	tok = *head;
	while (tok)
	{
		printf("%s$  %s\n", tok->value, tok->key);
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
		tok->value = ft_strdup(data);
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
