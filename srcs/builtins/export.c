/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 18:36:36 by bchabot           #+#    #+#             */
/*   Updated: 2022/12/20 14:31:59 by rlaforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_export(t_tok **head)
{
	t_tok	*tok;

	tok = *head;
	sort_export(head);
	while (tok)
	{
		if (tok->key && ft_strncmp(tok->key, "_", ft_strlen(tok->key) != 0))
		{
			if (!tok->value)
				printf("declare -x %s\n", tok->key);
			else
				printf("declare -x %s=\"%s\"\n", tok->key, tok->value);
		}
		tok = tok->next;
	}
}

void	free_struct(t_tok *head)
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
}

void	export(t_tok **head, char **args)
{
	t_tok	*env_copy;
	char	*key;
	char	*value;
	int		i;

	i = 0;
	env_copy = dup_env(head);
	if (!args)
		print_export(&env_copy);
	else
	{
		while (args[i])
		{
			key = ft_strtok(args[i], "=");
			value = ft_strtok(NULL, "\0");
			if (!value)
				newnode_back(head, NULL, key);
			else
				newnode_back(head, value, key);
			i++;
		}
	}
	free_struct(env_copy);
}

// PENSER A GERER LE += qui concatene la nouvelle chaine
//a celle deja presente dans value.
