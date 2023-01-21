/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_dir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benjaminchabot <benjaminchabot@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 20:08:33 by bchabot           #+#    #+#             */
/*   Updated: 2023/01/20 15:50:22 by benjamincha      ###   ########.fr       */
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

static void	no_file_directory(char *arg)
{	
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	exit_code = 1;
	return ;
}

static void	too_many_args(void)
{	
	ft_putstr_fd("minishell: cd: too many arguments\n", 2);
	exit_code = 1;
	return ;
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
	set_pwd(env, "OLDPWD", ft_getenv(env, "PWD"));
	if (chdir(args[1]) < 0)
	{
		no_file_directory(args[1]);
		return (1);
	}
	getcwd(str, sizeof(str));
	set_pwd(env, "PWD", str);
	return (0);
}
