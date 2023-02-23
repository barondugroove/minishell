/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchabot <bchabot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 12:26:12 by bchabot           #+#    #+#             */
/*   Updated: 2023/02/23 15:33:15 by bchabot          ###   ########.fr       */
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
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>

# define ERROR_CHAR '\x7F'
# define K_CMD "C"
# define K_ARG "A"
# define K_QUO "'"
# define K_DQUO "\""

extern int	g_exit_code;

typedef struct s_tok
{
	char			*key;
	char			*value;
	struct s_tok	*next;
}					t_tok;

typedef struct s_allocated
{
	t_tok	*env;
	t_tok	*cmd_head;
	char	**prompt;
	int		*pids;
	int		cmd_nbr;
	int		fd_reset[2];
}					t_allocated;

// BUILTINS
int			export(t_tok **head, char **args);
int			is_existing(t_tok **env, char *arg);
void		sort_export(t_tok **env_head);
int			has_equal(char *arg);
int			check_arg(char *arg);
int			unset(t_tok **env_head, char **key);
void		print_env(t_tok **head);
t_tok		*dup_env(t_tok **env_head);
int			pwd(char **args);
int			cd(char **args, t_tok *head);
void		echo(char **args);
int			exit_builtin(char **args, t_allocated *data);
void		ft_exit(t_allocated *data, long long code);
int			check_args_exit(char **args);
int			is_valid_number(const char *nptr);
t_tok		*find_next_cmd(t_tok *cmds, int nbr);

// EXECUTION
void		execution_controller(t_tok *env, t_tok *head, char **prompt);
int			has_pipe(t_tok *cmds);
int			is_regular_file(const char *path);
void		check_directory(char *command, char **args, t_allocated *data);
void		child_process(t_allocated *data, t_tok *cmd, \
			int *fd_pipe, int cmd_id);
int			execute_builtins(t_allocated *data, t_tok *cmds, int mode);
void		execute_cmd(t_allocated *data, t_tok *cmds, int mode);
void		multiple_executions(t_allocated *data, t_tok *cmds);

// REDIRECTION
void		handle_redirection(t_allocated *data, t_tok *cmd, int mode);
int			has_redir(t_tok *cmds);
t_tok		*redir_start(t_allocated *data, t_tok *cmd);
char		*get_file(t_tok *cmds, int nbr);
t_tok		*get_next_redir(t_tok *cmds);
int			check_file(char *file, int dir);
int			has_redir(t_tok *cmds);
char		*get_file(t_tok *cmds, int nbr);
int			redir_nbr(t_tok *cmds);
void		duplicator(int *fd_pipe, int fd_save, int cmd_id, int cmd_nbr);

// HEREDOC
int			heredoc_process(t_allocated *data, t_tok *cmd, int *fd_pipe);

// EXECUTION_UTILS
int			nb_cmds(t_tok *cmds);
char		**get_cmd(t_tok *cmds);
int			is_builtin(char *cmd);
char		*get_path(t_tok *env_tok, char *cmd);
char		**convert_envp(t_tok *head);

// LIST_UTILS
t_tok		*newtoken(char *data, char *key);
void		newtoken_back(t_tok **head, char *data, char *key);
void		replace_tok_value(char **val, char *new_val);

// FREE_UTILS
void		free_list(t_tok *head);
void		free_tab(char **tab);
void		free_allocated(t_allocated *data);

// FDS_UTILS
void		dup_multiple_fds(int fd[2], int fd_in, int fd_out);
void		close_multiple_fds(int fd[2]);

// PARSING
t_tok		*parsing_controller(t_tok *env, char **prompt);
char		*tokenizer(char *str);
void		add_token(t_tok **tok_head, char *str);
void		check_var_env(t_tok *env, char **prompt);

// UTILS
t_tok		*init_env(char **envp);
void		print_list(t_tok *head);
char		*c_to_str(char c);
char		*strjoin_pipex(char *s1, char *s2);
char		*ft_getenv(t_tok *env_head, char *key);
void		set_pwd(t_tok *head, char *key, char *path);
char		*test_relative_path(t_tok *env_tok, char *cmd);

// SIGNAL_UTILS
void		child_signal_controller(void);
void		child_c_handler(int sig);
void		ctrl_c_handler(int sig);
void		ft_ctrl_c_heredoc(int sig);
void		ft_ctrl_back_child(int sig);

// ERROR MESSAGES
void		no_file_msg(char *file, int code);
void		permission_denied_msg(char *file, int code);
void		is_dir_msg(char *file, int code);
void		no_cmd_msg(char *file, int code);
void		numeric_argument_required(char *arg);
void		error_message_export(char *arg);

#endif
