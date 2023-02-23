/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchabot <bchabot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 22:48:01 by bchabot           #+#    #+#             */
/*   Updated: 2023/02/23 20:43:46 by bchabot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_dir(const char *path)
{
	struct stat	path_stat;
	int			status;

	status = stat(path, &path_stat);
	if (status)
		return (0);
	if (S_ISDIR(path_stat.st_mode) == 1)
		return (1);
	return (0);
}

int	is_regular_file(const char *path)
{
	struct stat	path_stat;
	int			status;

	status = stat(path, &path_stat);
	if (status)
		return (0);
	if (S_ISREG(path_stat.st_mode) == 1)
		return (1);
	return (0);
}

int	right_test(char *command, int mode)
{
	struct stat	path_stat;

	stat(command, &path_stat);
	if (!(path_stat.st_mode & mode))
	{
		permission_denied_msg(command, 126);
		return (126);
	}
	return (0);
}

void	check_directory(char *command, char **args, t_allocated *data)
{
	if ((command[0] == '/' || ft_strncmp(command, "./", 2) == 0) \
		&& is_dir(command) == 1)
	{
		is_dir_msg(command, 126);
		free_tab(args);
		ft_exit(data, 126);
	}
	else if (!access(command, F_OK) \
		&& (command[0] == '/' || ft_strncmp(command, "./", 2) == 0))
	{
		if (right_test(command, S_IXUSR))
		{
			free_tab(args);
			ft_exit(data, 126);
		}
	}
	else if (access(command, F_OK) == -1 && (command[0] == '/' \
				|| ft_strncmp(command, "./", 2) == 0))
	{
		no_file_msg(command, 127);
		free_tab(args);
		ft_exit(data, 127);
	}
}

int	check_file(char *file, int dir)
{
	int	status;

	if (dir == 0 && !access(file, F_OK))
	{
		status = right_test(file, S_IWUSR);
		if (status)
			return (status);
		return (0);
	}
	if (dir == 1)
	{
		if (access(file, F_OK) == -1)
			return (0);
		if (right_test(file, S_IWUSR))
			return (1);
		return (0);
	}
	no_file_msg(file, 1);
	return (1);
}
