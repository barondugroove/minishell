/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchabot <bchabot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 12:09:31 by bchabot           #+#    #+#             */
/*   Updated: 2022/10/19 15:23:38 by bchabot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

int	ft_find_params(char s, va_list params)
{
	int	len;

	len = 0;
	if (s == 'c')
		len += ft_putchar(va_arg(params, int));
	else if (s == 's')
		len += ft_putstr(va_arg(params, char *));
	else if (s == 'p')
		len += ft_putptr(va_arg(params, unsigned long long));
	else if (s == 'd' || s == 'i')
		len += ft_putnbr(va_arg(params, int));
	else if (s == 'u')
		len += ft_putnbr_u(va_arg(params, unsigned long int));
	else if (s == 'x')
		len += ft_putnbr_base(va_arg(params, unsigned int), "0123456789abcdef");
	else if (s == 'X')
		len += ft_putnbr_base(va_arg(params, unsigned int), "0123456789ABCDEF");
	else if (s == '%')
		len += ft_putchar('%');
	return (len);
}

int	ft_printf(const char *s, ...)
{
	int		i;
	int		len;
	va_list	params;

	i = 0;
	len = 0;
	va_start(params, s);
	while (s[i])
	{
		if (s[i] == '%')
			len += ft_find_params(s[++i], params);
		else
			len += ft_putchar(s[i]);
		i++;
	}
	va_end(params);
	return (len);
}
