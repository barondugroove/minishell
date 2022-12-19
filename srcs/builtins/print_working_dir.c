/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_working_dir.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchabot <bchabot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 19:32:16 by bchabot           #+#    #+#             */
/*   Updated: 2022/12/14 17:29:05 by bchabot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	pwd(void)
{
	char	str[1024];

	getcwd(str, sizeof(str));
	ft_printf("%s\n", str);
	return ;
}
