/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 12:26:12 by bchabot           #+#    #+#             */
/*   Updated: 2023/01/25 16:34:33 by rlaforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

# define ERROR_CHAR '\x7F'
# define K_CMD "C"
# define K_ARG "A"
# define K_QUO "'"
# define K_DQUO "\""

extern int			g_g_exit_code;

typedef struct s_tok
{
	char			*key;
	char			*value;
	struct s_tok	*next;
}					t_tok;

typedef struct s_allocated
{
	t_tok			*env;
	t_tok			*cmd_head;
	int				*pids;
	int				cmd_nbr;
}					t_allocated;

// BUILTINS
int					export(t_tok **head, char **args);
void				print_env(t_tok **head);
t_tok				*dup_env(t_tok **env_head);
void				sort_export(t_tok **env_head);
int					has_equal(char *arg);
int					pwd(t_tok *env, char **args);
int					cd(char **args, t_tok *head);
void				echo(char **args);
void				unset(t_tok **env_head, char **key, t_tok *cmds);
int					exit_builtin(char **args);

// EXECUTION
void				execution_controller(t_tok *env, t_tok *tok_head);
int					has_pipe(t_tok *cmds);

// REDIRECTION
void				handle_redirection(t_tok *cmds);
int					has_redir(t_tok *cmds);
char				*get_file(t_tok *cmds);

// EXECUTION_UTILS
int					nb_cmds(t_tok *cmds);
char				**get_cmd(t_tok *cmds);
int					is_builtin(char *cmd);
char				*get_path(t_tok *env_tok, char *cmd);
char				**convert_envp(t_tok *head);

// FREE_UTILS
void				free_list(t_tok *head);
void				free_tab(char **tab);
void				free_truc(t_allocated *truc);

// PARSING
t_tok				*parsing_controller(t_tok *env, char *prompt);
char				*tokenizer(char *str);
void				add_token(t_tok *env, t_tok **tok_head, char *str);

// UTILS
t_tok				*init_env(char **envp);
t_tok				*newtoken(char *data, char *key);
void				newtoken_back(t_tok **head, char *data, char *key);
void				print_list(t_tok *head);
char				*c_to_str(char c);
char				*strjoin_pipex(char *s1, char *s2);
char				*ft_getenv(t_tok *env_head, char *key);
void				set_pwd(t_tok *head, char *key, char *path);
void				child_c_handler(int sig);

#endif
