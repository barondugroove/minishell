/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benjaminchabot <benjaminchabot@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 23:29:47 by benjamincha       #+#    #+#             */
/*   Updated: 2023/01/09 17:46:18 by benjamincha      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int is_n(char *args)
{
    int i;

    i = 0;
    if (!args)
        return (-1);
    if (args[0] == '-')
        i++;
    else
        return (0);
    while(args[i])
    {
        if (args[i++] != 'n')
            return (0);
    }
    return (1);
}

int echo(char **args)
{
    int i;

    i = 1;
    if (!args)
        return (-1);
    while (args[i])
    {
        if (!is_n(args[i]) || i != 1)
            printf("%s", args[i]);
        if (is_n(args[i]) && i != 1)
            printf(" ");
        else if (args[i + 1] && !is_n(args[i]))
            printf(" ");
        i++;
    }
    if (!args[1] || !is_n(args[1]))
       printf("\n");
    exit (0);
}