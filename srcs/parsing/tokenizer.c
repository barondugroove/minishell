/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchabot <bchabot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 18:11:47 by rlaforge          #+#    #+#             */
/*   Updated: 2022/12/19 16:03:35 by bchabot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"



/*

int	ft_tokenizer_ext(char *str)
{
	int		len;
	char	quote;

	len = 0;
	quote = '\0';
	while (*str && ((*str > 32 && *str != '|') || quote != '\0'))
	{
		if ((*str == '"' || *str == '\'') && quote == '\0')
			quote = *str;
		else if (*str == quote && quote != '\0')
			quote = '\0';
		//else if (*str == '|' && quote == '\0')
		//	return (len + 1);
		len++;
		str++;
	}
	if (quote != '\0')
	{
		//printf("Error: quote not closed");
	}
	//str++;
	return (len);
}

*/

int	ft_tokenizer_ext(char *str)
{
	int		len;
	char	quote;

	len = 0;
	quote = '\0';
	while (*str && (!(*str <= 32) || quote != '\0'))
	{
		if ((*str == '"' || *str == '\'') && quote == '\0')
			quote = *str;
		else if (*str == quote && quote != '\0')
			quote = '\0';
		else if (*str == '|' && *str + 1 <= 32 && quote == '\0')
			return (len + 1);
		len++;
		str++;
	}
	if (quote != '\0')
		return (-1);
	str++;
	return (len);
}

char	*tokenizer(char *str)
{
	static char	*save;
	int			i;

	if (str)
		save = str;
	if (!save)
		return (NULL);
	while (*save && *save <= 32)
		*save++ = 0;
	str = save;
	if (!*str)
		return (NULL);
	i = ft_tokenizer_ext(save);
	if (i == -1)
		*str = ERROR_CHAR;
	save += i;
	if (*save)
		*save++ = 0;
	if (*save == 0)
		save = NULL;
	return (str);
}