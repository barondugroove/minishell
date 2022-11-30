/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchabot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 14:52:47 by bchabot           #+#    #+#             */
/*   Updated: 2022/05/31 12:59:19 by bchabot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

int	ft_putnbr(int n)
{
	int				len;
	unsigned int	unsnb;

	unsnb = n;
	len = 0;
	if (n < 0)
	{
		len += ft_putchar('-');
		unsnb = -n;
	}
	if (unsnb < 10)
		len += ft_putchar(unsnb + '0');
	else
	{
		len += ft_putnbr(unsnb / 10);
		len += ft_putchar((unsnb % 10) + '0');
	}
	return (len);
}
