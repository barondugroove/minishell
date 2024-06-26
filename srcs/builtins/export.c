/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchabot <bchabot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 18:36:36 by bchabot           #+#    #+#             */
/*   Updated: 2023/02/23 16:28:11 by bchabot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_export(t_tok *head)
{
	t_tok	*tok;

	sort_export(&head);
	tok = head;
	while (tok)
	{
		if (ft_strncmp(tok->key, "_", 2) != 0
			&& tok->value && *tok->value != '\x7F')
			printf("declare -x %s=\"%s\"\n", tok->key, tok->value);
		else if (ft_strncmp(tok->key, "_", 2) != 0)
			printf("declare -x %s\n", tok->key);
		tok = tok->next;
	}
}

int	check_arg(char *arg)
{
	int	i;

	i = 0;
	if (!arg)
		return (1);
	if (arg[0] == '=' || (!ft_isalpha(arg[i]) || arg[0] == '_'))
		return (1);
	i++;
	while (arg[i] && (ft_isalnum(arg[i]) || arg[i] == '_'))
		i++;
	if (arg[i] == '+')
		i++;
	if (arg[i] && arg[i] != '=')
		return (1);
	if (arg[i] != '\0' && arg[i] != '=')
		return (1);
	return (0);
}

int	add_existing_var(t_tok **env, char *arg, char *key, char *value)
{
	t_tok	*tmp;

	tmp = *env;
	if (check_arg(key))
		return (1);
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key) && ft_strcmp(key, "_"))
		{
			if (has_equal(arg) == 2 && !ft_strcmp(tmp->value, "\x7F"))
			{
				free(tmp->value);
				tmp->value = ft_strdup(value);
			}
			else if (has_equal(arg) == 2 && tmp->value)
				tmp->value = ft_strjoin(tmp->value, value);
			else if (!value && has_equal(arg) == 1)
				tmp->value = ft_strdup("\0");
			else if (!tmp->value)
				tmp->value = ft_strdup(value);
			return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}

int	add_var(t_tok **env, char *args)
{
	char	*arg_copy;
	char	*key;
	char	*value;
	int		status;

	arg_copy = ft_strdup(args);
	key = ft_strtok(arg_copy, "=");
	value = ft_strtok(NULL, "\0");
	status = 0;
	if (check_arg(key))
	{
		error_message_export(key);
		return (1);
	}
	if (is_existing(env, ft_strtok(key, "+")))
		status = add_existing_var(env, args, key, value);
	else if (!value && has_equal(args) == 1)
		newtoken_back(env, ft_strdup("\0"), ft_strdup(key));
	else if (value && has_equal(args))
		newtoken_back(env, ft_strdup(value), ft_strdup(key));
	else
		newtoken_back(env, ft_strdup("\x7F"), ft_strdup(key));
	free(arg_copy);
	return (status);
}

int	export(t_tok **env, char **args)
{
	int		i;
	int		status;

	i = 0;
	status = 0;
	if (!args[1])
		print_export(*env);
	while (args[++i])
		status = add_var(env, args[i]);
	return (status);
}
