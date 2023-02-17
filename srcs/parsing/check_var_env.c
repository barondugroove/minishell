/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_var_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 23:08:59 by rlaforge          #+#    #+#             */
/*   Updated: 2023/02/16 23:08:59 by rlaforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	cat_var_to_prompt(char **prompt, char *ptr, char *value, char *end)
{
	char	*str;

	str = malloc(sizeof(char) * (ft_strlen(*prompt)
				+ ft_strlen(value) + ft_strlen(end) + 1));
	str[ft_strlen(*prompt) + ft_strlen(value) + ft_strlen(end)] = '\0';
	ft_strlcpy(str, *prompt, ptr - *prompt + 1);
	if (value)
		ft_strcat(str, value);
	ft_strcat(str, end);
	free(*prompt);
	*prompt = str;
}

void	replace_var_env(t_tok *env, char **prompt, char *ptr)
{
	char	*end;
	char	*value;
	char	*var;
	int		varlen;

	end = ptr;
	varlen = 0;
	while (*end != '"' && *end != ' ' && *end != '\0' && end++)
		varlen++;
	var = malloc(sizeof(char) * (varlen + 1));
	ft_strlcpy(var, end - varlen, varlen + 1);
	if (*(var + 1) && *(var + 1) == '?')
	{
		value = ft_itoa(g_exit_code);
		end = ptr + 2;
	}
	else
		value = ft_strdup(ft_getenv(env, var + 1));
	cat_var_to_prompt(prompt, ptr, value, end);
	free(var);
	free(value);
}

void	check_var_env(t_tok *env, char **prompt)
{
	char	*ptr;
	char	quote;

	quote = '\0';
	ptr = *prompt;
	while (*ptr)
	{
		if (*ptr == '$' && *(ptr + 1) && *(ptr + 1) != '"'
			&& *(ptr + 1) != ' ' && *(ptr + 1) != '$' && quote != '\'')
		{
			replace_var_env(env, prompt, ptr);
			ptr = *prompt;
			quote = '\0';
		}
		else if (quote == '\0' && (*ptr == '"' || *ptr == '\''))
			quote = *ptr;
		else if (*ptr == quote && quote != '\0')
			quote = '\0';
		ptr++;
	}
}
