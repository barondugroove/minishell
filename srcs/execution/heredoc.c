/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchabot <bchabot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 15:22:58 by bchabot           #+#    #+#             */
/*   Updated: 2023/02/13 19:44:07 by bchabot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	how_many_heredoc(t_tok *cmd)
{
	t_tok	*tmp;
	int		i;

	tmp = cmd;
	i = 0;
	while (tmp && *tmp->key != '|')
	{
		if (ft_strcmp(tmp->key, "<<") == 0)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

void	launch_heredoc(char *delim, int *fd_pipe)
{
	char	*str;

	str = get_next_line(0);
	while (1)
	{
		if (ft_strcmp(str, delim) == 0)
			break ;
		write(fd_pipe[1], str, ft_strlen(str));
		str = get_next_line(0);
	}
}

t_tok	*next_heredoc(t_tok *cmds)
{
	t_tok	*tmp;

	tmp = cmds;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "<<") == 0)
		{
			if (*tmp->next->key == 'F')
				return (tmp);
		}
		tmp = tmp->next;
	}
	return (tmp);
}

void	heredoc_process(t_tok *cmd)
{
	t_tok	*tmp;
	int		pipe_heredoc[2];
	int		nbr;


	tmp = cmd;
	nbr = how_many_heredoc(tmp);
	pipe(pipe_heredoc);
	while (nbr--)
	{
		launch_heredoc(tmp->next->value, pipe_heredoc);
		tmp = next_heredoc(tmp);
	}
}
