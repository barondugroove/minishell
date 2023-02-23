/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benjaminchabot <benjaminchabot@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 23:52:11 by benjamincha       #+#    #+#             */
/*   Updated: 2023/02/23 00:35:51 by benjamincha      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	child_signal_controller(void)
{
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, child_c_handler);
}

void	ft_ctrl_back_child(int sig)
{
	(void)sig;
	g_exit_code = 139;
	printf("Quit (core dumped)\n");
}

void	child_c_handler(int sig)
{
	(void)sig;
	g_exit_code = 130;
	printf("\n");
}

void	ctrl_c_handler(int sig)
{
	(void)sig;
	g_exit_code = 130;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	ft_ctrl_c_heredoc(int sig)
{
	(void)sig;
	g_exit_code = 130;
	close(0);
}
