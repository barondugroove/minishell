/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcspn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchabot <bchabot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 15:52:31 by bchabot           #+#    #+#             */
/*   Updated: 2022/12/19 16:03:23 by bchabot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcspn(char *s, const char *rejects)
{
	char	*tmp;

	tmp = s;
	while (*tmp)
	{
		if (ft_strchr(rejects, *tmp))
			return (tmp - s);
		tmp++;
	}
	return (tmp - s);
}
