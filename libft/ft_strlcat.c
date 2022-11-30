/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchabot <bchabot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 16:15:20 by bchabot           #+#    #+#             */
/*   Updated: 2022/10/19 15:26:25 by bchabot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

int	ft_strlcat(char *dst, const char *src, int size)
{
	int	dl;
	int	sl;
	int	i;

	dl = ft_strlen(dst);
	sl = ft_strlen(src);
	i = 0;
	if (size == 0 || dl > size)
		return (size + sl);
	if (!*src)
		return (dl);
	while (src[i] && (dl + i) < size - 1)
	{
		dst[dl + i] = src[i];
		i++;
	}
	dst[dl + i] = '\0';
	return (dl + sl);
}
