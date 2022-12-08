/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 18:11:47 by bchabot           #+#    #+#             */
/*   Updated: 2022/12/08 18:56:02 by rlaforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_strcspn(char *str, const char *delim)
{
	int	len;
	int	quote;

	len = 0;
	quote = 0;
	while (*str && (!ft_strchr(delim, *str) || quote))
	{
		if (*str == '"' && !quote)
			quote = 1;
		else if (*str == '"' && quote)
			quote = 0;
		else if (*str == '"' && (str[1] == ' ' || !str[1]) && quote)
			return (len + 1);
		len++;
		str++;
	}
	return (len);
}

char	*ft_strtok(char *str, const char *delim)
{
	int			len;
	char		*tok;
	static char	*save;

	if (str)
		save = str;
	if (*save == '\0')
		return (NULL);
	len = ft_strcspn(save, delim);
	tok = malloc((sizeof(char) * len) + 1);
	memcpy(tok, save, len);
	tok[len] = '\0';
	save += len;
	if (*save != '\0')
		save++;
	return (tok);
}
