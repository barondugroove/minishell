/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_pipe_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 00:46:23 by rlaforge          #+#    #+#             */
/*   Updated: 2022/12/22 00:46:23 by rlaforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	pipe_error(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '|' && str[i + 1] == '|')
		{
			*str = ERROR_CHAR;
			return (1);
		}
		i++;
	}
	return (0);
}

void	add_pipe_token_ext(t_tok *tok_head, char *str)
{
	int	i;

	i = 0;
	if (str[0] == '|')
	{
		newtoken_back(&tok_head, ft_strdup("|"), ft_strdup(K_PIPE));
		newtoken_back(&tok_head, ft_substr(str, 1, 
			ft_strlen(str)), ft_strdup(K_ARG));
	}
	else
	{
		while (str[i] != '|')
			i++;
		newtoken_back(&tok_head, ft_substr(str, 0, i), ft_strdup(K_ARG));
		newtoken_back(&tok_head, ft_strdup("|"), ft_strdup(K_PIPE));
		newtoken_back(&tok_head, ft_substr(str, i + 1, 
			ft_strlen(str)), ft_strdup(K_CMD));
	}
}

int	add_pipe_token(t_tok *tok_head, char *str)
{
	if (pipe_error(str))
		return (1);
	if (str[0] == '|' && !str[1])
		newtoken_back(&tok_head, ft_strdup("|"), ft_strdup(K_PIPE));
	else if (str[ft_strlen(str) - 1] == '|')
	{
		newtoken_back(&tok_head, ft_substr(str, 0, 
			ft_strlen(str) - 1), ft_strdup(K_ARG));
		newtoken_back(&tok_head, ft_strdup("|"), ft_strdup(K_PIPE));
	}
	else
		add_pipe_token_ext(tok_head, str);
	return (0);
}
