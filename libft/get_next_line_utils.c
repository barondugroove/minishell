/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchabot <bchabot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 11:11:24 by bchabot           #+#    #+#             */
/*   Updated: 2022/10/19 15:47:35 by bchabot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_substr_gnl(char *s, int start, int len)
{
	char			*buf;
	int				i;
	int				x;

	i = 0;
	if (s == 0 || !len)
		return (NULL);
	x = ft_strlen(s);
	if (start >= x)
	{
		buf = malloc(sizeof(char));
		if (!buf)
			return (NULL);
		*buf = '\0';
		return (buf);
	}
	if (len >= x)
		len = x - start;
	buf = malloc(sizeof(char) * len + 1);
	if (!buf)
		return (NULL);
	while (len-- && (start + len) <= x)
		buf[i++] = s[start++];
	buf[i] = '\0';
	return (buf);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*tab;
	int		longueur;

	if (!s1)
		return (NULL);
	longueur = ft_strlen(s1) + ft_strlen(s2) + 1;
	tab = malloc(sizeof(char) * longueur);
	if (!tab)
		return (NULL);
	ft_strlcpy(tab, s1, longueur);
	ft_strlcat(tab, s2, longueur);
	free(s1);
	return (tab);
}

int	ft_strlcat_gnl(char *dst, char *src, int size)
{
	int	dl;
	int	sl;
	int	i;

	dl = ft_strlen(dst);
	sl = ft_strlen(src);
	i = 0;
	if (size == 0 || dl > size)
		return ((int)size + sl);
	if (!*src)
		return ((int)dl);
	while (src[i] && (dl + i) < size - 1)
	{
		dst[dl + i] = src[i];
		i++;
	}
	dst[dl + i] = '\0';
	return ((int)dl + sl);
}

int	ft_strlcpy_gnl(char *dst, char *src, int size)
{
	int			i;
	char		*str;

	i = 0;
	str = (char *)src;
	if (!size)
		return ((int)ft_strlen(src));
	while (str[i] && i < size - 1)
	{
		dst[i] = str[i];
		i++;
	}
	dst[i] = '\0';
	return ((int)ft_strlen(src));
}
