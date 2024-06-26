# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bchabot <bchabot@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/13 12:26:21 by bchabot           #+#    #+#              #
#    Updated: 2023/02/23 20:41:06 by bchabot          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = srcs/main.c \
		srcs/parsing/parsing_controller.c \
		srcs/parsing/tokenizer.c \
		srcs/parsing/add_token.c \
		srcs/parsing/check_var_env.c \
		srcs/execution/execution_controller.c \
		srcs/execution/execution_utils.c \
		srcs/execution/redirections.c \
		srcs/execution/redirections_utils.c \
		srcs/execution/execute_with_pipes.c \
		srcs/execution/heredoc.c \
		srcs/execution/check_files.c \
		srcs/builtins/export.c \
		srcs/builtins/export_utils.c \
		srcs/builtins/unset.c \
		srcs/builtins/print_working_dir.c \
		srcs/builtins/change_dir.c \
		srcs/builtins/env.c \
		srcs/builtins/echo.c \
		srcs/builtins/exit.c \
		srcs/builtins/exit_utils.c \
		srcs/parsing/init_env.c \
		srcs/utils/utils.c \
		srcs/utils/list_utils.c \
		srcs/utils/signal_utils.c \
		srcs/utils/free_utils.c \
		srcs/utils/fds_utils.c \
		srcs/utils/error_msgs.c

CC = @gcc

CFLAGS = -Wall -Wextra -Werror -g

LIBFT = libft/libft.a

OBJS = $(SRCS:.c=.o)

all : logo message $(NAME)
	@echo "\e[2A\e[91m                                                                    \033[0m"

%.o : %.c
	@echo "\033[1A\e[1mCompiling $<                                                       \033[0m"
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT) :
		@make -sC libft

logo :
	@echo "\n\e[0;95m┏━┓\e[96m╋\e[95m┏┓┏┳┓\e[96m╋\e[95m┏━┓\e[96m╋╋╋╋╋\e[0;95m┏┓           "
	@echo "\e[0;95m┃\e[5;96m╋\e[0;95m┣━┫┗╋┫┗┓┃┏╋━┳━┳┳╋╋┓┏┓┏━┓┏━┳━┓"
	@echo "\e[0;95m┃┏┫┻┫┏┫┃┏┫┃┗┫\e[5;96m╋\e[0;95m┃\e[5;96m╋\e[0;95m┃┃┃┃┗┫┗┫\e[5;96m╋\e[0;95m┗┫\e[5;96m╋\e[0;95m┃┻┫"
	@echo "\e[0;95m┗┛┗━┻━┻┻━┛┗━┻━┻┓┣━┻┻━┻━┻━━╋┓┣━┛"
	@echo "\e[0;96m╋╋╋╋╋╋╋╋╋╋╋╋╋╋╋\e[95m┗┛\e[96m╋╋╋╋╋╋╋╋╋\e[0;95m┗━┛\033[0m\n"

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(OBJS) $(CFLAGS) $(LIBFT) -lreadline -o $(NAME)
	@echo "\e[2A\e[1;32m📦 $(NAME) compiled!                                           \n\n\033[0m"

message:
	@echo "\e[1;5m🗜️  $(NAME) compiling...\n\033[0m"

clean :
	@rm -f $(OBJS)
	@make -sC libft fclean
	@echo "\033[91m🧹 Binary files cleaned!\033[0m"

fclean : clean
	@rm -rf $(NAME)
	@echo "\e[1A\e[91m🧹 Binary files and executable cleaned!\033[0m"


re : fclean all

.PHONY : all re clean fclean logo message
