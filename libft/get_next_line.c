/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchabot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 14:12:20 by bchabot           #+#    #+#             */
/*   Updated: 2022/06/29 12:09:39 by bchabot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

int	ft_has_n(char *s, int param)
{
	int	i;

	i = 0;
	if (param)
	{
		while (s[i])
		{
			if (s[i] == '\n')
				return (i + 1);
			i++;
		}
		return (0);
	}
	else
	{
		while (s[i])
		{
			if (s[i] == '\n')
				return (i + 1);
			i++;
		}
	}
	return (i);
}

char	*ft_read(char *str, int fd)
{
	char	*buff;
	int		i;

	i = 1;
	buff = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	*buff = 0;
	while (!ft_has_n(str, 1) && i)
	{
		i = read(fd, buff, BUFFER_SIZE);
		buff[i] = '\0';
		str = ft_strjoin_gnl(str, buff);
	}
	free(buff);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*save;
	char		*str;
	char		*line;

	str = malloc(sizeof(char));
	if (!str)
		return (NULL);
	*str = 0;
	if (read(fd, str, 0) == -1 || fd < 0 || BUFFER_SIZE < 1)
		return (free(str), NULL);
	if (!save)
	{
		save = malloc(sizeof(char));
		if (!save)
			return (NULL);
		*save = 0;
	}
	str = ft_strjoin_gnl(str, save);
	free(save);
	str = ft_read(str, fd);
	save = ft_substr_gnl(str, ft_has_n(str, 0), \
	ft_strlen(str) - ft_has_n(str, 0));
	line = ft_substr_gnl(str, 0, ft_has_n(str, 0));
	free(str);
	return (line);
}
