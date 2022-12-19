/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strspn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchabot <bchabot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 15:51:27 by bchabot           #+#    #+#             */
/*   Updated: 2022/12/19 16:03:10 by bchabot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

int	ft_strspn(char *s, const char *accepts)
{
	int	i;

	i = 0;
	while (s[i] && ft_strchr(accepts, s[i]))
		i++;
	return (i);
}
