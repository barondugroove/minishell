/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benjaminchabot <benjaminchabot@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 18:36:36 by bchabot           #+#    #+#             */
/*   Updated: 2023/02/21 02:20:13 by benjamincha      ###   ########.fr       */
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

int	check_errors_export(char *arg)
{
	int	i;

	i = 0;
	if (!arg || arg[0] == '+')
	{
		error_message_export(arg);
		return (1);
	}
	while (arg[i] && arg[i] != '=')
	{
		if ((!ft_isalpha(arg[i]) && i == 0 && arg[i] != '_') || arg[i] <= 32)
		{
			error_message_export(arg);
			return (1);
		}
		else if ((!ft_isalpha(arg[i]) && ft_isdigit(arg[i]) && !ft_isalpha(arg[0]) && arg[0] != '_'))
		{
			error_message_export(arg);
			return (1);
		}
		i++;
	}
	return (0);
}

int	add_existing_var(t_tok **env, char *arg)
{
	t_tok	*tmp;
	char	*key;
	char	*value;
	char	*arg_copy;

	tmp = *env;
	arg_copy = ft_strdup(arg);
	key = ft_strtok(arg_copy, "+=");
	value = ft_strtok(NULL, "\0");
	if (check_errors_export(key))
		return (1);
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			if (has_equal(arg) == 2)
				tmp->value = ft_strjoin(tmp->value, value + 1);
			else if (!value && has_equal(arg) == 1)
				tmp->value = ft_strdup("\0");
			else if (!tmp->value)
				tmp->value = ft_strdup(value);
			free(arg_copy);
			return (0);
		}
		tmp = tmp->next;
	}
	free(arg_copy);
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
	if (check_errors_export(ft_strtok(key, "+")))
		return (1);
	if (is_existing(env, key))
		status = add_existing_var(env, args);
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
