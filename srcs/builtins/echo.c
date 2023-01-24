/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 23:29:47 by benjamincha       #+#    #+#             */
/*   Updated: 2023/01/24 13:41:29 by rlaforge         ###   ########.fr       */
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

void echo(char **args)
{
    int i;

    i = 1;
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
}
