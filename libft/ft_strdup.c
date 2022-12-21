/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchabot <bchabot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 16:15:07 by bchabot           #+#    #+#             */
/*   Updated: 2022/12/20 20:14:05 by bchabot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_strdup(const char *s)
{
	int		i;
	char	*dest;

	if (!s)
		return (NULL);
	i = ft_strlen(s);
	dest = malloc(sizeof(char) * i + 1);
	if (dest == NULL)
		return (NULL);
	ft_strcpy(dest, (char *)s);
	return (dest);
}
