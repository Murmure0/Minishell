#!/bin/bash

SRCS =	main.c			\

OBJS = $(SRCS:.c=.o)

NAME = minishell

RM = rm -f

CC = gcc

CFLAGS = -Wall -Wextra -Werror
CFLAGS += -g

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -lreadline -o $(NAME)

all: $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
