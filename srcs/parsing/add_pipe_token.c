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

void	add_pipe_token(t_tok *tok_head, char *str)
{
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
}
