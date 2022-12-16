/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 18:11:47 by rlaforge          #+#    #+#             */
/*   Updated: 2022/12/16 15:09:34 by rlaforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_strcspn(char *str)
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
		else if ((*str == '"' || *str == '\'') && (*str <= 32 || !*str)
			&& quote != '\0')
			return (len + 1);
		len++;
		str++;
	}
	if (quote != '\0')
	{
		printf("Error: quote not closed");
		exit(1);
	}
	str++;
	return (len);
}

char	*tokenizer(char *str, char *sep)
{
	static char	*save;

	if (str)
		save = str;
	if (!save || !sep)
		return (NULL);

	while (*save && *save <= 32)
		*save++ = 0;
	str = save;
	if (!*str)
		return (NULL);
	save += ft_strcspn(save);
	if (*save)
		*save++ = 0;
	if (*save == 0)
		save = NULL;
	return (str);
}