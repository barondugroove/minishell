/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 18:11:47 by rlaforge          #+#    #+#             */
/*   Updated: 2022/12/13 18:39:01 by rlaforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_strcspn(char *str)
{
	int		len;
	char	quote;

	len = 0;
	quote = '\0';
	//while (*str && (!(*str <= 32) || quote != '\0'))
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
		printf("Error: quotes not closed");
		exit(1);
	}
	str++;
	return (len);
}

char	*ft_strtok(char *str)
{
	int			len;
	char		*tok;
	static char	*save;

	if (str)
		save = str;
	if (*save == '\0')
		return (NULL);
	len = ft_strcspn(save);
	tok = malloc((sizeof(char) * len) + 1);
	if (!tok)
		return (NULL);
	ft_memcpy(tok, save, len);
	tok[len] = '\0';
	save += len;
	if (*save != '\0')
		save++;
	if (!tok)
		return (NULL);
	return (tok);
}
