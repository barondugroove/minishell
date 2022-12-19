/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 12:26:12 by bchabot           #+#    #+#             */
/*   Updated: 2022/12/18 20:50:47 by rlaforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <limits.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

#  define ERROR_CHAR '\x7F'

typedef struct s_tok {
	char	*key;
	char	*value;
	void	*next;
}	t_tok;

// CHECK_ERRORS

// LEXER
void	ft_lexer(char *prompt);

// PARSER

// INIT_DATA
void	init_env(char **envp);

// UTILS
char	*tokenizer(char *str);
t_tok	*newnode(char *data, char *key);
void	newnode_back(t_tok **head, char *data, char *key);
void	print_list(t_tok *head);
void	free_list(t_tok *head);

#endif
