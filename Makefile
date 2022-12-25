# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/13 12:26:21 by bchabot           #+#    #+#              #
#    Updated: 2022/12/24 18:01:26 by rlaforge         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = srcs/main.c \
		srcs/parsing/parser.c \
		srcs/parsing/tokenizer.c \
		srcs/parsing/add_pipe_token.c \
		srcs/parsing/add_quote_token.c \
		srcs/utils/utils.c \
		srcs/parsing/init_env.c \
		srcs/builtins/export.c \
		srcs/builtins/export_utils.c \
		srcs/builtins/unset.c \
		srcs/builtins/print_working_dir.c \
		srcs/builtins/change_dir.c \
		srcs/builtins/env.c \
		srcs/execution/executions.c

CC = gcc

LIBFT = libft/libft.a

CFLAGS = -lreadline -Wall -Wextra -Werror -g

NAME = minishell

OBJS = $(SRCS:.c=.o)

all : $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT) :
		make -sC libft
		@echo "\033[92mLibft compiled."

minish :
	@echo "\n\e[0;95m┏━┓\e[96m╋\e[95m┏┓┏┳┓\e[96m╋\e[95m┏━┓\e[96m╋╋╋╋╋\e[0;95m┏┓           "
	@echo "\e[0;95m┃\e[5;96m╋\e[0;95m┣━┫┗╋┫┗┓┃┏╋━┳━┳┳╋╋┓┏┓┏━┓┏━┳━┓"
	@echo "\e[0;95m┃┏┫┻┫┏┫┃┏┫┃┗┫\e[5;96m╋\e[0;95m┃\e[5;96m╋\e[0;95m┃┃┃┃┗┫┗┫\e[5;96m╋\e[0;95m┗┫\e[5;96m╋\e[0;95m┃┻┫"
	@echo "\e[0;95m┗┛┗━┻━┻┻━┛┗━┻━┻┓┣━┻┻━┻━┻━━╋┓┣━┛"
	@echo "\e[0;96m╋╋╋╋╋╋╋╋╋╋╋╋╋╋╋\e[95m┗┛\e[96m╋╋╋╋╋╋╋╋╋\e[0;95m┗━┛\n"

$(NAME): minish $(OBJS) $(LIBFT)
	$(CC) $(OBJS) $(CFLAGS) $(LIBFT) -o $(NAME)


clean :
	rm -f $(OBJS)
	make -sC libft fclean
	@echo "\033[91mObjects cleaned."

fclean : clean
	rm -rf $(NAME)
	@echo "\033[91mObjects and program cleaned."

re : fclean all

.PHONY : all re clean fclean minish
.SILENT :
