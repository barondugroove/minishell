/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benjaminchabot <benjaminchabot@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 18:19:29 by benjamincha       #+#    #+#             */
/*   Updated: 2023/01/09 18:19:47 by benjamincha      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_getenv(t_tok *env_head, char *key)
{
	t_tok	*tmp;

	tmp = env_head;
	if (!key)
		return (NULL);
	while (tmp && ft_strncmp(tmp->key, key, ft_strlen(tmp->key)) != 0)
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
		if (tok->value != NULL && ft_strncmp(tok->key, "_", ft_strlen(tok->key)) != 0)
			printf("%s=%s\n", tok->key, tok->value);
		tok = tok->next;
	}
	exit(0);
}
