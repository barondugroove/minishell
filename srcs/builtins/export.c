/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 18:36:36 by bchabot           #+#    #+#             */
/*   Updated: 2022/12/22 01:20:35 by rlaforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_export(t_tok **head)
{
	t_tok	*tok;
	t_tok	*env_copy;

	tok = *head;
	env_copy = dup_env(head);
	sort_export(head);
	while (tok)
	{
		if (ft_strncmp(tok->key, "_", ft_strlen(tok->key) != 0))
			printf("declare -x %s=\"%s\"\n", tok->key, tok->value);
		tok = tok->next;
	}
	free_list(env_copy);
}

void	export(t_tok **env, char **args)
{
	char	*key;
	char	*value;
	char	*arg_copy;
	int		i;

	i = 0;
	if (!args)
		print_export(env);
	else
	{
		while (args[i])
		{
			arg_copy = ft_strdup(args[i]);
			key = ft_strtok(arg_copy, "=");
			value = ft_strtok(NULL, "\0");
			newtoken_back(env, ft_strdup(value), ft_strdup(key));
			free(arg_copy);
			i++;
		}
	}
}

// PENSER A GERER LE += qui concatene la nouvelle chaine
//a celle deja presente dans value.
