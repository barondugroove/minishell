/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchabot <bchabot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 18:19:29 by benjamincha       #+#    #+#             */
/*   Updated: 2023/01/31 20:43:55 by bchabot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


//
//
// PROBLEME QUAND JE FAIT ECHO $PWD. probleme quand je met une var d'env avec un / dans sa value.
//
//
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
		if (*tok->value != '\x7F' && ft_strcmp(tok->key, "_") != 0)
			printf("%s=%s\n", tok->key, tok->value);
		tok = tok->next;
	}
}
