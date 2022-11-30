/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchabot <bchabot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 16:59:32 by bchabot           #+#    #+#             */
/*   Updated: 2022/10/19 15:36:58 by bchabot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_substr(char const *s, int start, int len)
{
	char			*buf;
	int				i;
	int				x;

	i = 0;
	if (s == 0)
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
	buf = malloc(sizeof(char) * (len + 1));
	if (!buf)
		return (NULL);
	while (len-- && (start + len) <= x)
		buf[i++] = s[start++];
	buf[i] = '\0';
	return (buf);
}
