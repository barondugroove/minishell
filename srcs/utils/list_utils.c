/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchabot <bchabot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 23:21:57 by bchabot           #+#    #+#             */
/*   Updated: 2023/02/23 20:41:42 by bchabot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
