/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benjaminchabot <benjaminchabot@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 13:45:58 by benjamincha       #+#    #+#             */
/*   Updated: 2023/02/15 22:49:04 by benjamincha      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/***************************************************\
||                                                 ||
||   Need to handle here_doc                       ||
||                                                 ||
\***************************************************/

void	set_redir_out(t_tok *tmp, int dir)
{
	int	fd_out;

	fd_out = -1;
	check_file(tmp->next->value, 1);
	if (dir == 3)
		fd_out = open(tmp->next->value, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else
		fd_out = open(tmp->next->value, O_CREAT | O_WRONLY | O_APPEND, 0644);
	dup2(fd_out, 1);
	if (fd_out != -1)
		close(fd_out);
	return ;
}

void	set_redir_in(t_tok *cmd, t_tok *tmp, int dir)
{
	int	fd_in;

	fd_in = -1;
	if (dir == 1)
		check_file(tmp->next->value, 0);
	if (dir == 1 && is_builtin(cmd->value) != 2)
		fd_in = open(tmp->next->value, O_RDONLY, 0644);
	else
		return ;
	dup2(fd_in, 0);
	if (fd_in != -1)
		close(fd_in);
	return ;
}

int	redir_start(t_tok *cmd)
{
	t_tok	*tmp;

	tmp = cmd;
	while (tmp)
	{
		if (*tmp->key == '<' || *tmp->key == '>')
			return (1);
		else if (*tmp->key == *K_CMD)
			return (0);
		tmp = tmp->next;
	}
	return (0);
}

void	handle_redirection(t_allocated *data, t_tok *cmd)
{
	int		nbr;
	t_tok	*tmp;

	if (redir_start(data->cmd_head))
		tmp = get_next_redir(data->cmd_head);
	else
		tmp = get_next_redir(cmd);
	nbr = redir_nbr(tmp);
	while (nbr--)
	{
		if (has_redir(tmp) == 2)
			heredoc_process(data, tmp);
		if (has_redir(tmp) > 2)
			set_redir_out(tmp, has_redir(tmp));
		else if (has_redir(tmp) == 1)
			set_redir_in(cmd, tmp, has_redir(tmp));
		if (nbr)
			tmp = get_next_redir(tmp->next);
	}
}
