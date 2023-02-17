/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fds_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchabot <bchabot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 02:36:33 by bchabot           #+#    #+#             */
/*   Updated: 2023/02/17 18:04:19 by bchabot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	close_multiple_fds(int fd[2])
{
	close(fd[0]);
	close(fd[1]);
}

void	dup_multiple_fds(int fd[2], int fd_in, int fd_out)
{
	dup2(fd[0], fd_in);
	dup2(fd[1], fd_out);
}
