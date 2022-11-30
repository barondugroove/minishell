/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchabot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 11:34:54 by bchabot           #+#    #+#             */
/*   Updated: 2022/04/06 12:37:54 by bchabot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	unsnb;

	unsnb = n;
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		unsnb = -n;
	}
	if (unsnb < 10)
		ft_putchar_fd(unsnb + '0', fd);
	else
	{
		ft_putnbr_fd(unsnb / 10, fd);
		ft_putchar_fd((unsnb % 10) + '0', fd);
	}
}
