/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchabot <bchabot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 23:18:25 by benjamincha       #+#    #+#             */
/*   Updated: 2023/02/21 16:39:01 by bchabot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_allocated(t_allocated *data)
{
	if (data->cmd_nbr == 1)
	{
		dup2(data->fd_reset[0], 0);
		dup2(data->fd_reset[1], 1);
		close(data->fd_reset[0]);
		close(data->fd_reset[1]);
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
