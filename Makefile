# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/11 13:08:44 by mberthet          #+#    #+#              #
#    Updated: 2022/01/12 16:13:05 by mberthet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc

# CFLAGS = -Wall -Wextra -Werror
# CFLAGS += -g

MAIN = 	srcs/main.c			\
		srcs/init_struct.c	\
		srcs/env.c			\
		./exec/exec.c \
		./exec/here_doc.c \

SOURCES = $(MAIN)

LIBFT = ./libft/libft.a

OBJECTS = $(SOURCES:.c=.o)

HEADER = minishell.h

all : $(NAME)

$(NAME): $(OBJECTS) $(HEADER)
		@$(CC) $(CFLAGS) $(OBJECTS) -L./libft -lft -o $(NAME)

$(LIBFT):
	$(MAKE) -C ./libft

clean:
	/bin/rm -f $(OBJECTS) && cd ./libft/ && make clean
	
fclean: clean
	/bin/rm -f $(NAME) && cd ./libft/ && make fclean
	
re: fclean all

.PHONY: clean fclean re all
