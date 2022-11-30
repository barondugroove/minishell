/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchabot <bchabot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 14:52:25 by bchabot           #+#    #+#             */
/*   Updated: 2022/10/19 15:21:48 by bchabot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	*ft_memmove(void *dest, const void *src, int n)
{
	char	*d;
	char	*s;

	d = (char *)dest;
	s = (char *)src;
	if (n == 0)
		return (dest);
	if (d < s)
		ft_memcpy(d, s, n);
	else if (d > s)
		while (n--)
			d[n] = s[n];
	return (d);
}
