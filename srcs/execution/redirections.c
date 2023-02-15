/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchabot <bchabot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 13:45:58 by benjamincha       #+#    #+#             */
/*   Updated: 2023/02/15 16:59:35 by bchabot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/***************************************************\
||                                                 ||
||   Need to handle here_doc                       ||
||                                                 ||
\***************************************************/

int	is_dir(const char *path)
{
	struct stat	path_stat;

	stat(path, &path_stat);
	return (S_ISDIR(path_stat.st_mode));
}

int	is_regular_file(const char *path)
{
	struct stat	path_stat;

	stat(path, &path_stat);
	return (S_ISREG(path_stat.st_mode));
}

int	check_directory(char *command)
{
	struct stat	path_stat;

	if ((command[0] == '/' || ft_strncmp(command, "./",
				2) == 0) && is_dir(command) == 1)
	{
		is_dir_msg(command, 126);
		return (126);
	}
	else if (!access(command, F_OK) && \
	(command[0] == '/' || ft_strncmp(command, "./", 2) == 0))
	{
		stat(command, &path_stat);
		if (!(path_stat.st_mode & S_IXUSR))
		{
			permission_denied_msg(command, 126);
			return (126);
		}
	}
	else if (access(command, F_OK) == -1 \
	&& (command[0] == '/' || ft_strncmp(command, "./", 2) == 0))
	{
		no_file_msg(command, 127);
		return (127);
	}
	return (0);
}

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
	if(dir == 1 && is_builtin(cmd->value) != 2)
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
