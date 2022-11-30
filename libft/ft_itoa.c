/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchabot <bchabot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 11:27:20 by bchabot           #+#    #+#             */
/*   Updated: 2022/10/19 15:17:01 by bchabot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

static int	ft_intlen(int n)
{
	int	i;

	i = 1;
	while (n >= 10 || n <= -10)
	{
		i++;
		n /= 10;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char			*tab;
	int				i;
	unsigned int	x;
	int				neg;

	x = n;
	neg = 0;
	if (n < 0)
	{
		x = -n;
		neg = 1;
	}
	i = ft_intlen(n);
	tab = malloc(sizeof(char) * ((i += neg) + 1));
	if (!tab)
		return (NULL);
	if (neg)
		tab[0] = '-';
	tab[i] = '\0';
	while (i-- > neg)
	{
		tab[i] = (x % 10) + '0';
		x /= 10;
	}
	return (tab);
}
