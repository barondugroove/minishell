/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchabot <bchabot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 14:23:19 by bchabot           #+#    #+#             */
/*   Updated: 2022/10/19 15:20:53 by bchabot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	*ft_memcpy(void *dest, const void *src, int n)
{
	int		i;
	char	*dst;
	char	*sc;

	i = 0;
	dst = (char *)dest;
	sc = (char *)src;
	if (!dst && !sc)
		return (NULL);
	while (i < n)
	{
		dst[i] = sc[i];
		i++;
	}
	return (dest);
}
