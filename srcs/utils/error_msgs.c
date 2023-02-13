/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msgs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchabot <bchabot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 19:46:05 by bchabot           #+#    #+#             */
/*   Updated: 2023/02/13 15:14:28 by bchabot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	no_file_msg(char *file, int code)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	g_exit_code = code;
}

void	permission_denied_msg(char *file, int code)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": Permission denied\n", 2);
	g_exit_code = code;
}

void	is_dir_msg(char *file, int code)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": Is a directory\n", 2);
	g_exit_code = code;
}

void	no_cmd_msg(char *file, int code)
{
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": command not found\n", 2);
	g_exit_code = code;
}
