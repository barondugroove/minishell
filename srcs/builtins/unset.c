/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchabot <bchabot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 18:41:41 by bchabot           #+#    #+#             */
/*   Updated: 2023/02/23 15:33:12 by bchabot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	error_message_unset(char *arg)
{
	ft_putstr_fd("minishell: unset: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": not a valid identifier\n", 2);
	return ;
}

void	remove_node(t_tok **head, t_tok *node_to_remove)
{
	t_tok	*buf;

	buf = *head;
	if (*head == NULL || node_to_remove == NULL)
		return ;
	if (*head == node_to_remove && node_to_remove->next)
	{
		*head = (*head)->next;
		free(buf->key);
		free(buf->value);
		free(buf);
		return ;
	}
	while (buf->next && buf->next != node_to_remove)
		buf = buf->next;
	buf->next = node_to_remove->next;
	free(node_to_remove->key);
	free(node_to_remove->value);
	free(node_to_remove);
}

int	unset(t_tok **env_head, char **key)
{
	t_tok	*tmp;
	int		i;

	tmp = *env_head;
	i = 0;
	while (key[++i])
	{
		while (tmp)
		{
			if (check_arg(key[i]))
			{
				error_message_unset(key[i]);
				return (1);
			}
			if (!ft_strcmp(tmp->key, key[i]))
			{
				remove_node(env_head, tmp);
				tmp = *env_head;
				break ;
			}
			else
				tmp = tmp->next;
		}
	}
	return (0);
}
