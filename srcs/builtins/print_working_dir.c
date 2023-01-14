/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_working_dir.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benjaminchabot <benjaminchabot@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 19:32:16 by bchabot           #+#    #+#             */
/*   Updated: 2023/01/14 03:43:54 by benjamincha      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	pwd(t_tok *env)
{
	char	*str;

	str = ft_strdup(ft_getenv(env, "PWD"));
	printf("%s\n", str);
	free(str);
}
