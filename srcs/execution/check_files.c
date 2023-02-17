/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benjaminchabot <benjaminchabot@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 22:48:01 by benjamincha       #+#    #+#             */
/*   Updated: 2023/02/17 02:31:42 by benjamincha      ###   ########.fr       */
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

int	check_directory(char *command)
{
	int	status;

	if ((command[0] == '/' || ft_strncmp(command, "./", 2) == 0) \
		&& is_dir(command) == 1)
	{
		is_dir_msg(command, 126);
		return (126);
	}
	else if (!access(command, F_OK) \
		&& (command[0] == '/' || ft_strncmp(command, "./", 2) == 0))
	{
		status = right_test(command, S_IXUSR);
		if (status)
			return (status);
	}
	else if (access(command, F_OK) == -1 && (command[0] == '/' \
				|| ft_strncmp(command, "./", 2) == 0))
	{
		no_file_msg(command, 127);
		return (127);
	}
	return (0);
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
