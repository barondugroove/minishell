/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 23:29:47 by benjamincha       #+#    #+#             */
/*   Updated: 2022/12/29 01:47:09 by rlaforge         ###   ########.fr       */
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
        if (!args[1] || !is_n(args[i]))
            printf("%s", args[i]);
        if (args[i + 1])
            printf(" ");
        i++;
    }
    if (!args[1] || !is_n(args[1]))
       printf("\n");
    return (0);
}