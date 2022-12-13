/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 18:11:47 by rlaforge          #+#    #+#             */
/*   Updated: 2022/12/13 18:05:12 by rlaforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_strcspn(char *str)
{
	int	len;
	int	quote;
	int	squote;

	len = 0;
	quote = 0;
	squote = 0;
	while (*str && (!(*str <= 32) || (quote || squote)))
	{
		if (*str == '"' && !squote)
			quote = !quote;
		else if (*str == '|' && (!quote || !squote))
			return (len);
		else if (*str == '\'' && !quote)
			squote = !squote;
		else if ((*str == '"' || *str == '\'') && (*str <= 32 || !*str)
			&& (quote || squote))
			return (len + 1);
		len++;
		str++;
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
