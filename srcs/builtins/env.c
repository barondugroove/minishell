/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchabot <bchabot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 18:19:29 by bchabot           #+#    #+#             */
/*   Updated: 2023/02/23 20:43:24 by bchabot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_getenv(t_tok *env_head, char *key)
{
	t_tok	*tmp;

	tmp = env_head;
	if (!key)
		return (NULL);
	while (tmp && ft_strcmp(tmp->key, key) != 0)
		tmp = tmp->next;
	if (!tmp)
		return (NULL);
	return (tmp->value);
}

void	print_env(t_tok **head)
{
	t_tok	*tok;

	tok = *head;
	while (tok)
	{
		if (*tok->value != '\x7F')
			printf("%s=%s\n", tok->key, tok->value);
		tok = tok->next;
	}
}
