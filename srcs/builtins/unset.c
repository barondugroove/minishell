/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchabot <bchabot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 18:41:41 by bchabot           #+#    #+#             */
/*   Updated: 2023/02/07 18:28:14 by bchabot          ###   ########.fr       */
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

int	check_errors_unset(char *arg)
{
	int	i;

	i = 0;
	if (!arg)
		return (1);
	while (arg[i])
	{
		if ((!ft_isalpha(arg[i]) && i == 0) || arg[i] <= 32)
			return (1);
		else if ((ft_isdigit(arg[i]) && i == 0))
			return (1);
		i++;
	}
	return (0);
}

int	unset(t_tok **env_head, char **key)
{
	t_tok	*tmp;
	int		i;

	tmp = *env_head;
	i = 1;
	while (key[i])
	{
		while (tmp)
		{
			if (check_errors_unset(key[i]))
			{
				error_message_unset(key[i]);
				return (1);
				break ;
			}
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
	return (0);
}
