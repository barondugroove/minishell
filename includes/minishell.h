/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benjaminchabot <benjaminchabot@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 12:26:12 by bchabot           #+#    #+#             */
/*   Updated: 2023/01/14 03:36:22 by benjamincha      ###   ########.fr       */
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
# define K_CMD "C"
# define K_ARG "A"
# define K_QUO "'"
# define K_DQUO "\""

extern int	exit_code;

typedef struct s_tok {
	char			*key;
	char			*value;
	struct s_tok	*next;
}	t_tok;

// CHECK_ERRORS

// BUILTINS
void	export(t_tok **head, char **args, t_tok *cmds);
void	print_env(t_tok **head);
t_tok	*dup_env(t_tok **env_head);
void	sort_export(t_tok **env_head);
void	pwd(t_tok *env);
int		cd(char **args, t_tok *head, t_tok *cmds);
void	set_pwd(t_tok *head, char *key, char *path);
char	*ft_getenv(t_tok *env_head, char *key);
void 	echo(char **args);
void	unset(t_tok **env_head, char **key, t_tok *cmds);

// EXECUTION
void	execution_controller(t_tok *env, t_tok *tok_head);
int		has_pipe(t_tok *cmds);

// EXECUTION_UTILS
int		nb_cmds(t_tok *cmds);
char	**get_cmd(t_tok *cmds);
int		is_builtin(char *cmd);
char	*get_path(t_tok *env_tok, char *cmd);
char	**convert_envp(t_tok *head);

// FREE_UTILS
void	free_list(t_tok *head);
void	free_tab(char **tab);

// PARSING
t_tok	*parsing_controller(t_tok *env, char *prompt);
char	*tokenizer(char *str);
void	add_token(t_tok **tok_head, char *str);

// INIT_DATA
t_tok	*init_env(char **envp);

// UTILS
t_tok	*newtoken(char *data, char *key);
void	newtoken_back(t_tok **head, char *data, char *key);
void	print_list(t_tok *head);
char 	*c_to_str(char c);
char	*strjoin_pipex(char *s1, char *s2);

#endif
