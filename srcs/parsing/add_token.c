/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 17:57:55 by rlaforge          #+#    #+#             */
/*   Updated: 2023/01/25 16:38:53 by rlaforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	clean_token(t_tok **tok_head, char *str)
{
	char	quote;
	int		i;
	int		len;

	quote = '\0';
	len = ft_strlen(str);
	i = 0;
	while (i < len)
	{
		if ((str[i] == '"' || str[i] == '\'') && quote == '\0')
		{
			quote = str[i];
			ft_memmove(str + i, str + i + 1, len - i);
			len--;
		}
		else if (str[i] == quote && quote != '\0')
		{
			quote = '\0';
			ft_memmove(str + i, str + i + 1, len - i);
			len--;
		}
		else if ((str[i] == '|' || str[i] == '<' || str[i] == '>')
			&& quote == '\0')
		{
			newtoken_back(tok_head, ft_substr(str, 0, i), ft_strdup(K_ARG));
			newtoken_back(tok_head, c_to_str(str[i]), c_to_str(str[i]));
			ft_memmove(str, str + i + 1, len - i);
			i = 0;
			len = ft_strlen(str);
		}
		else
			i++;
	}
}

// Need to cat ce qui as de collé apres le $?. genre: echo $?HELLO = 0HELLO
void	replace_var_env(t_tok *env, char *str, char *ptr)
{
	char	*newStr;
	char	*end;
	char	*value;
	char	*var;
	int		varlen;

	end = ptr;
	varlen = 0;
	while (*end != '"' && *end != ' ' && *end != '\0')
	{
		varlen++;
		end++;
	}
	var = malloc(sizeof(char) * (varlen + 1));
	ft_strlcpy(var, end - varlen, varlen + 1);
	if (*(var + 1) && *(var + 1) == '?')
		value = ft_itoa(g_exit_code);
	else
		value = ft_getenv(env, var + 1);
	newStr = malloc(sizeof(char) * ((ft_strlen(value) + ft_strlen(end)) + 1));
	ft_strlcpy(newStr, str, ptr - str + 1);
	if (value)
		ft_strcat(newStr, value);
	ft_strcat(newStr, end);
	ft_strcpy(str, newStr);
	free(var);
	free(newStr);
}

void	check_var_env(t_tok *env, char *str)
{
	char	*ptr;
	char	quote;

	quote = '\0';
	ptr = str;
	while (*ptr)
	{
		if (*ptr == '$' && *(ptr + 1) && *(ptr + 1) != '"' && (quote == '\0' || quote == '"'))
			replace_var_env(env, str, ptr);
		if ((*ptr == '"' || *ptr == '\'') && quote == '\0')
			quote = *ptr;
		else if (*ptr == quote && quote != '\0')
			quote = '\0';
		ptr++;
	}
}

void	add_token(t_tok *env, t_tok **tok_head, char *str)
{
	check_var_env(env, str);
	if (ft_strchr(str, '"') || ft_strchr(str, '\'') || ft_strchr(str, '|')
			|| ft_strchr(str, '<') || ft_strchr(str, '>'))
	{
		while (*str == '|' || *str == '<' || *str == '>')
		{
			newtoken_back(tok_head, c_to_str(str[0]), c_to_str(str[0]));
			ft_memmove(str, str + 1, ft_strlen(str));
		}
		clean_token(tok_head, str);
	}
	if (*str)
		newtoken_back(tok_head, ft_strdup(str), ft_strdup(K_ARG));
}
