/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_dir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchabot <bchabot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 20:08:33 by bchabot           #+#    #+#             */
/*   Updated: 2023/02/20 19:57:07 by bchabot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	too_many_args(void)
{
	ft_putstr_fd("minishell: cd: too many arguments\n", 2);
	g_exit_code = 1;
	return ;
}

void	set_pwd(t_tok *head, char *key, char *path)
{
	t_tok	*tmp;

	if (!path)
		return ;
	tmp = head;
	while (tmp && ft_strncmp(tmp->key, key, ft_strlen(key)) != 0)
		tmp = tmp->next;
	if (tmp == NULL)
		return ;
	free(tmp->value);
	tmp->value = ft_strdup(path);
}

static int	args_nbr(char **args)
{
	int	i;

	i = 1;
	while (args[i])
		i++;
	return (i - 1);
}

int	cd(char **args, t_tok *env)
{
	char	str[4096];

	if (args_nbr(args) >= 2)
	{
		too_many_args();
		return (1);
	}
	if (!args[1])
	{
		set_pwd(env, "OLDPWD", ft_getenv(env, "PWD"));
		chdir(ft_getenv(env, "HOME"));
		getcwd(str, sizeof(str));
		set_pwd(env, "PWD", str);
		return (0);
	}
	if (chdir(args[1]) < 0)
	{
		no_file_msg(str, 1);
		return (1);
	}
	set_pwd(env, "OLDPWD", getcwd(str, sizeof(str)));
	getcwd(str, sizeof(str));
	set_pwd(env, "PWD", str);
	return (0);
}
