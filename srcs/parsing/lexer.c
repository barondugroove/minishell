/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 17:36:49 by bchabot           #+#    #+#             */
/*   Updated: 2022/12/13 18:45:52 by rlaforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_lexer(char *prompt)
{
	char	*str;
	//char	sep[] = {' ', '<', '>', '|'};
	t_tok	*tok_head;

	tok_head = NULL;
	//split sur les |, les cmd sont dans un tableau, ensuite on tokenize chaques cmd.
	str = ft_strtok(prompt);
	newnode(&tok_head, str, NULL);
	while (str)
	{
		str = ft_strtok(NULL);
		newnode(&tok_head, str, NULL);
	}
	free(str);
	print_list(&tok_head);
}
