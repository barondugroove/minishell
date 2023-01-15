/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilslol.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benjaminchabot <benjaminchabot@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 15:46:52 by benjamincha       #+#    #+#             */
/*   Updated: 2023/01/14 14:01:10 by benjamincha      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    fd_closer(int fds[2], int pipe_fds[2])
{
    if (fds[0] == pipe_fds[0] && fds[1] == pipe_fds[1])
        return ;
    else if (fds[0] == pipe_fds[0] && fds[1] == STDOUT_FILENO)
        close(pipe_fds[1]);
    else if (fds[0] == STDIN_FILENO && fds[1] == pipe_fds[1])
        close(pipe_fds[0]);        
}

void	duplicator(int fd_in, int fd_out)
{
	if (fd_in != STDIN_FILENO)
	{
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}
	if (fd_out != STDOUT_FILENO)
	{
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
	}
}

int	has_pipe(t_tok *cmds)
{
	t_tok *tmp;

	tmp = cmds;
	while (tmp->next)
	{
		if (*tmp->key == '|')
			return (1);
		tmp = tmp->next;
	}
	return (0);
}