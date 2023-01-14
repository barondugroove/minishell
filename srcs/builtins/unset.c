/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benjaminchabot <benjaminchabot@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 18:41:41 by bchabot           #+#    #+#             */
/*   Updated: 2023/01/14 03:26:31 by benjamincha      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	remove_node(t_tok **head, t_tok *node_to_remove)
{
	t_tok	*current;

	current = *head;
	if (*head == NULL || node_to_remove == NULL)
		return ;
	if (*head == node_to_remove)
	{
		*head = node_to_remove->next;
		return ;
	}
	while (current->next != node_to_remove && current->next)
		current = current->next;
	current->next = node_to_remove->next;
	free(node_to_remove->key);
	free(node_to_remove->value);
	free(node_to_remove);
}

void	unset(t_tok **env_head, char **key, t_tok *cmds)
{
	t_tok	*tmp;
	int		i;

	tmp = *env_head;
	i = 1;
	if (has_pipe(cmds))
		exit (0);
	while (key[i])
	{
		while (tmp)
		{
			if (ft_strncmp(tmp->key, key[i], ft_strlen(tmp->key)) == 0)
			{
				remove_node(env_head, tmp);
				tmp = *env_head;
				break ;
			}
			else
				tmp = tmp->next;
		}
		i++;
	}
}
