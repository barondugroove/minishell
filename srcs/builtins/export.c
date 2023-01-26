/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 18:36:36 by bchabot           #+#    #+#             */
/*   Updated: 2023/01/26 18:31:41 by rlaforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_export(t_tok **head)
{
	t_tok	*tok;
	t_tok	*env_copy;

	env_copy = dup_env(head);
	sort_export(&env_copy);
	tok = env_copy;
	while (tok)
	{
		if (ft_strncmp(tok->key, "_", ft_strlen(tok->key) != 0)
			&& *tok->value != '\0')
			printf("declare -x %s=\"%s\"\n", tok->key, tok->value);
		else if (ft_strncmp(tok->key, "_", ft_strlen(tok->key) != 0))
			printf("declare -x %s\n", tok->key);
		tok = tok->next;
	}
	free_list(env_copy);
}

void	add_existing_var(t_tok *env, char *arg)
{
	t_tok	*tmp;

	tmp = env;
	while (tmp->next)
	{
		if (ft_strncmp(tmp->value, arg, ft_strlen(tmp->value) == 0))
			ft_strlcat(tmp->value, arg, ft_strlen(arg));
		tmp = tmp->next;
	}
}

static void	error_message_export(char *arg)
{
	ft_putstr_fd("minishell: export: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": not a valid identifier\n", 2);
	return ;
}

int	check_errors_export(char *args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (args[i] == '=' && ft_isalpha(args[i]))
			break ;
		if (args[i] <= 32 || (!ft_isalpha(args[i]) && args[i] != '_'))
		{
			error_message_export(args);
			return (1);
		}
		i++;
	}
	return (0);
}

int	export(t_tok **env, char **args)
{
	char	*key;
	char	*value;
	char	*arg_copy;
	int		i;

	if (!args[1])
		print_export(env);
	else
	{
		i = 0;
		while (args[++i])
		{
			if (check_errors_export(args[i]))
				return (2);
			if (has_equal(args[i]))
			{
				arg_copy = ft_strdup(args[i]);
				key = ft_strtok(arg_copy, "=");
				value = ft_strtok(NULL, "\0");
				newtoken_back(env, ft_strdup(value), ft_strdup(key));
				free(arg_copy);
			}
			else
			{
				arg_copy = ft_strdup(args[i]);
				key = ft_strtok(arg_copy, "=");
				newtoken_back(env, ft_strdup("\0"), ft_strdup(key));
				free(arg_copy);
			}
		}
	}
	return (0);
}

// PENSER A GERER LE += qui concatene la nouvelle chaine
//a celle deja presente dans value.