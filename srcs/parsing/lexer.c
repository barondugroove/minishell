/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 17:36:49 by bchabot           #+#    #+#             */
/*   Updated: 2022/12/12 19:31:26 by rlaforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_lexer(char *prompt)
{
	char	*str;
	//char	sep[] = {' ', '<', '>', '|'};
	t_tok	*tok_head;

	tok_head = NULL;
	printf("Prompt is :%s\n\n", prompt);
	str = ft_strtok(prompt);
	newnode(&tok_head, str, "lol");
	while (str)
	{
		str = ft_strtok(NULL);
		newnode(&tok_head, str, "lol");
	}
	free(str);
	print_list(&tok_head);
}
