# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/13 12:26:21 by bchabot           #+#    #+#              #
#    Updated: 2022/12/25 19:17:13 by rlaforge         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = srcs/main.c \
		srcs/parsing/parsing_controller.c \
		srcs/execution/execution_controller.c \
		srcs/parsing/tokenizer.c \
		srcs/parsing/add_token.c \
		srcs/utils/utils.c \
		srcs/parsing/init_env.c \
		srcs/builtins/export.c \
		srcs/builtins/export_utils.c \
		srcs/builtins/unset.c \
		srcs/builtins/print_working_dir.c \
		srcs/builtins/change_dir.c \
		srcs/builtins/env.c

CC = @gcc

LIBFT = libft/libft.a

CFLAGS = -lreadline -Wall -Wextra -Werror -g

NAME = minishell

OBJS = $(SRCS:.c=.o)

all : minish message $(NAME)
	@echo "\e[1A\e[91m                                                 \033[0m"

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT) :
		@make -sC libft

minish :
	@echo "\n\e[0;95m┏━┓\e[96m╋\e[95m┏┓┏┳┓\e[96m╋\e[95m┏━┓\e[96m╋╋╋╋╋\e[0;95m┏┓           "
	@echo "\e[0;95m┃\e[5;96m╋\e[0;95m┣━┫┗╋┫┗┓┃┏╋━┳━┳┳╋╋┓┏┓┏━┓┏━┳━┓"
	@echo "\e[0;95m┃┏┫┻┫┏┫┃┏┫┃┗┫\e[5;96m╋\e[0;95m┃\e[5;96m╋\e[0;95m┃┃┃┃┗┫┗┫\e[5;96m╋\e[0;95m┗┫\e[5;96m╋\e[0;95m┃┻┫"
	@echo "\e[0;95m┗┛┗━┻━┻┻━┛┗━┻━┻┓┣━┻┻━┻━┻━━╋┓┣━┛"
	@echo "\e[0;96m╋╋╋╋╋╋╋╋╋╋╋╋╋╋╋\e[95m┗┛\e[96m╋╋╋╋╋╋╋╋╋\e[0;95m┗━┛\033[0m\n"

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(OBJS) $(CFLAGS) $(LIBFT) -o $(NAME)
	@echo "\033[1A\e[1;32m📦 $(NAME) compiled!     \n\033[0m"

message:
	@echo "\e[1;5m🗜️  $(NAME) compiling...\033[0m"

clean :
	@rm -f $(OBJS)
	@make -sC libft fclean
	@echo "\033[91m🧹 Binary files cleaned!\033[0m"

fclean : clean
	@rm -rf $(NAME)
	@echo "\e[1A\e[91m🧹 Binary files and executable cleaned!\033[0m"


re : fclean all

.PHONY : all re clean fclean minish message
