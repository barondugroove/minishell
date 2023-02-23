/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchabot <bchabot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 17:51:32 by bchabot           #+#    #+#             */
/*   Updated: 2023/02/23 20:45:50 by bchabot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	*ft_memchr(const void *s, int c, int n)
{
	int				i;
	unsigned char	*str;
	unsigned char	ch;

	str = (unsigned char *)s;
	i = -1;
	ch = (unsigned char)c;
	while (++i < n)
	{
		if (str[i] == ch)
			return ((void *)str + i);
	}
	return (NULL);
}
