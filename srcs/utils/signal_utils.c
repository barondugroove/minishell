/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchabot <bchabot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 23:52:11 by benjamincha       #+#    #+#             */
/*   Updated: 2023/02/23 19:48:35 by bchabot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_ctrl_c_heredoc(int sig)
{
	(void)sig;
	g_exit_code = -2;
	close(0);
}

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
