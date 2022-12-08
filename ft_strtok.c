/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchabot <bchabot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 18:11:47 by bchabot           #+#    #+#             */
/*   Updated: 2022/12/08 18:14:51 by bchabot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	len_tok(char *str, char *delimiters)
{
	int	i;
	int	j;
	int	pos;

	i = 0;
	pos = 0;
	while (str[i] == ' ')
		i++;
	while (str[i])
	{
		j = 0;
		while (delimiters[j])
		{
			if (str[i] != delimiters[j])
				j++;
			else if (str[i] == ' ')
				return (pos + 1);
			else
				return (pos);
		}
		pos++;
		i++;
	}
	return (pos);
}

char	*ft_strtok(char *str, char *delimiters)
{
	int			len;
	int			i;
	char		*line;
	static char	*save;

	i = 0;
	if (!save)
		save = ft_strdup(str);
	len = len_tok(save, delimiters);
	if (!len)
	{
		save = NULL;
		return (NULL);
	}
	line = malloc(sizeof(char) * len + 1);
	if (!line)
		return (NULL);
	line[len] = '\0';
	while (i < len)
	{
		line[i] = save[i];
		i++;
	}
	save += len;
	return (line);
}
