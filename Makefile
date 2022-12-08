# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bchabot <bchabot@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/13 12:26:21 by bchabot           #+#    #+#              #
#    Updated: 2022/12/08 17:05:39 by bchabot          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = srcs/main.c \
		srcs/parsing/lexer.c \
		srcs/parsing/environment_variables.c \
		ft_strtok.c \

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

.PHONY : all re clean fclean
.SILENT :
