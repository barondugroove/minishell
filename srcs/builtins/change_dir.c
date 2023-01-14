/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_dir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benjaminchabot <benjaminchabot@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 20:08:33 by bchabot           #+#    #+#             */
/*   Updated: 2023/01/14 03:43:47 by benjamincha      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	set_pwd(t_tok *head, char *key, char *path)
{
	t_tok	*tmp;

	tmp = head;
	while (tmp && ft_strncmp(tmp->key, key, ft_strlen(key)) != 0)
		tmp = tmp->next;
	free(tmp->value);
	tmp->value = ft_strdup(path);
}

int	cd(char **args, t_tok *env, t_tok *cmds)
{
	char	str[4096];
	
	if (has_pipe(cmds))
		exit (0);
	if (!args[1])
	{
		set_pwd(env, "OLDPWD", ft_getenv(env, "PWD"));
		chdir(ft_getenv(env, "HOME"));
		getcwd(str, sizeof(str));
		set_pwd(env, "PWD", str);
		return (0);
	}	
	set_pwd(env, "OLDPWD", ft_getenv(env, "PWD"));
	if (chdir(args[1]) < 0)
	{
		printf("minishell: cd: %s: No such file or directory\n", args[1]);
		return (errno);
	}
	getcwd(str, sizeof(str));
	set_pwd(env, "PWD", str);
	return (0);
}
