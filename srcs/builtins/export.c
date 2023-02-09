/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benjaminchabot <benjaminchabot@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 18:36:36 by bchabot           #+#    #+#             */
/*   Updated: 2023/02/09 01:11:16 by benjamincha      ###   ########.fr       */
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
		if (ft_strncmp(tok->key, "_", ft_strlen(tok->key) != 0)
			&& tok->value && *tok->value != '\x7F')
			printf("declare -x %s=\"%s\"\n", tok->key, tok->value);
		else if (ft_strncmp(tok->key, "_", ft_strlen(tok->key) != 0))
			printf("declare -x %s\n", tok->key);
		tok = tok->next;
	}
}

void	error_message_export(char *arg)
{
	ft_putstr_fd("minishell: export: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": not a valid identifier\n", 2);
	return ;
}

int	check_errors_export(char *arg)
{
	int	i;

	i = 0;
	if (!arg)
		return (1);
	while (arg[i])
	{
		if ((!ft_isalpha(arg[i]) && i == 0) || arg[i] <= 32)
			return (1);
		else if ((!ft_isalpha(arg[i]) && arg[i] != '_'))
			return (1);
		i++;
	}
	return (0);
}

int	add_existing_var(t_tok **env, char *args)
{
	t_tok	*tmp;
	char	*key;
	char	*value;
	char	*arg_copy;

	tmp = *env;
	arg_copy = ft_strdup(args);
	key = ft_strtok(arg_copy, "+=");
	value = ft_strtok(NULL, "\0");
	if (check_errors_export(key))
	{
		error_message_export(args);
		return (1);
	}
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			if (has_equal(args) == 2)
				tmp->value = ft_strjoin(tmp->value, value);
			else if (!value && has_equal(args) == 1)
				tmp->value = ft_strdup("\0");
			else
				tmp->value = ft_strdup(value);
			return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}

int	add_var(t_tok **env, char *key, char *value)
{
	if (check_errors_export(key))
	{
		error_message_export(key);
		return (1);
	}
	if (!value)
		newtoken_back(env, ft_strdup("\x7F"), ft_strdup(key));
	else
		newtoken_back(env, ft_strdup(value), ft_strdup(key));
	return (0);
}

int	export(t_tok **env, char **args)
{
	char	*arg_copy;
	char	*key;
	char	*value;
	int		i;
	int		status;

	i = 0;
	status = 0;
	if (!args[1])
	{
		print_export(*env);
		return (status);
	}
	while (args[++i])
	{
		arg_copy = ft_strdup(args[i]);
		key = ft_strtok(arg_copy, "+=");
		value = ft_strtok(NULL, "\0");
		if (!key)
		{
			error_message_export(args[i]);
			return (1);
		}
		if (is_existing(env, key))
			status = add_existing_var(env, args[i]);
		else
			status = add_var(env, key, value);
		free(arg_copy);
	}
	return (status);
}
