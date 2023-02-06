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

void	add_token(t_tok **tok_head, char *str)
{
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
