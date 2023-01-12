/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_working_dir.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 19:32:16 by bchabot           #+#    #+#             */
/*   Updated: 2023/01/12 20:28:35 by rlaforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	pwd(char **args, t_tok *env)
{
	char	str[1024];

	getcwd(str, sizeof(str));
	printf("%s\n", str);
	//free_list(env);
	//free_tab(args);
	(void)args;
	(void)env;
	//exit(0);
}
