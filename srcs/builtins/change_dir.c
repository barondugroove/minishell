/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_dir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchabot <bchabot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 20:08:33 by bchabot           #+#    #+#             */
/*   Updated: 2022/12/20 16:06:11 by bchabot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	set_pwd(t_tok *head, char *key, char *path)
{
	t_tok	*tmp;

	tmp = head;
	while (tmp && ft_strncmp(tmp->key, key, ft_strlen(key)) != 0)
		tmp = tmp->next;
	tmp->value = path;
}

int	cd(char *path, t_tok *head)
{
	char	str[1024];

	if (!path)
		return (1);
	set_pwd(head, "OLDPWD", ft_getenv(head, "PWD"));
	if (chdir(path) < 0)
	{
		printf("minishell: cd: %s: No such file or directory\n", path);
		return (errno);
	}
	getcwd(str, sizeof(str));
	set_pwd(head, "PWD", str);
	return (0);
}
