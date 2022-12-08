/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 17:36:49 by bchabot           #+#    #+#             */
/*   Updated: 2022/12/08 16:54:51 by rlaforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_lexer(char *prompt)
{
	int		i;
	char	*str;
	char	sep[] = {' ', '<', '>', '|'};

	i = 0;
	printf("starting prompt is : %s\n\n", prompt);
	while (prompt[i])
	{
		if (prompt[i] == '<' || prompt[i] == '>')
			printf("token is redir\n");
		else if (prompt[i] == '|')
			printf("token is pipe\n");
		else if (prompt[i] == 39 || prompt[i] == '"')
			printf("token is quote\n");
		else if (prompt[i] <= 32)
			printf("token is sep\n");
		else
			printf("token is literal\n");
		i++;
	}
	str = ft_strtok(prompt, sep);
	while (str)
	{
		printf("Token's str is :%s:\n", str);
		str = ft_strtok(NULL, sep);
	}
	free(str);
}