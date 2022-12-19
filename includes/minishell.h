/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchabot <bchabot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 12:26:12 by bchabot           #+#    #+#             */
/*   Updated: 2022/12/19 18:26:23 by bchabot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <limits.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

# define ERROR_CHAR '\x7F'

typedef struct s_tok {
	char			*key;
	char			*value;
	struct s_tok	*next;
}	t_tok;

// CHECK_ERRORS

// BUILTINS
void	export(t_tok **head, char **args);
void	print_env(t_tok **head);
t_tok	*dup_env(t_tok **env_head);
void	sort_export(t_tok **env_head);
void	pwd(void);
int		cd(char *path, t_tok *head);
void	set_pwd(t_tok *head, char *key, char *path);
char	*ft_getenv(t_tok *env_head, char *key);

// LEXER
void	ft_lexer(char *prompt);

// PARSER

// INIT_DATA
t_tok	*init_env(char **envp);

// UTILS
char	*tokenizer(char *str);
t_tok	*newnode(char *data, char *key);
void	newnode_back(t_tok **head, char *data, char *key);
void	print_list(t_tok *head);
void	free_list(t_tok *head);
void	free_struct(t_tok *head);

#endif
