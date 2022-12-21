/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchabot <bchabot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 19:43:13 by bchabot           #+#    #+#             */
/*   Updated: 2022/12/20 20:58:04 by bchabot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_getenv(t_tok *env_head, char *key)
{
	char	*str;
	t_tok	*tmp;

	tmp = env_head;
	while (tmp && ft_strncmp(tmp->key, key, ft_strlen(key)) != 0)
		tmp = tmp->next;
	str = ft_strdup(tmp->value);
	return (str);
}

void	print_env(t_tok **head)
{
	t_tok	*tok;

	tok = *head;
	while (tok)
	{
		if (tok->value != NULL && ft_strncmp(tok->key, "_", ft_strlen(tok->key) != 0))
			printf("%s=%s\n", tok->key, tok->value);
		tok = tok->next;
	}
}
