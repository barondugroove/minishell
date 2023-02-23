/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchabot <bchabot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 23:18:25 by bchabot           #+#    #+#             */
/*   Updated: 2023/02/23 20:42:08 by bchabot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_allocated(t_allocated *data)
{
	if (data->cmd_nbr <= 1)
	{
		dup_multiple_fds(data->fd_reset, 0, 1);
		close_multiple_fds(data->fd_reset);
	}
	free_list(data->env);
	free_list(data->cmd_head);
	free(*data->prompt);
	free(data->pids);
}

void	free_list(t_tok *head)
{
	t_tok	*tmp;

	tmp = head;
	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
	free(head);
	head = NULL;
}

void	free_tab(char **tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}
