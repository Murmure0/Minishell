# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/11 13:08:44 by mberthet          #+#    #+#              #
#    Updated: 2022/01/12 11:32:27 by vmasse           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc

CFLAGS = -Wall -Wextra -Werror

MAIN = main.c \

SOURCES = $(MAIN)

OBJECTS = $(SOURCES:.c=.o)

HEADER = minishell.h

all : $(NAME)

$(NAME): $(OBJECTS) $(HEADER)
			@$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME)

clean:
	/bin/rm -f $(OBJECTS) $(BOBJECTS) all
	
fclean: clean
	/bin/rm -f $(NAME) all
	
re: fclean all

.PHONY: clean fclean re all

