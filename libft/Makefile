#!/bin/bash

SRCS =	ft_bzero.c	\
		ft_split.c	\
		ft_strlen.c	\
		ft_strjoin.c	\
		ft_strtrim.c	\
		ft_strncmp.c	\
		ft_substr.c	\
		ft_strdup.c	\
		ft_strchr_pos.c	\
		is_space.c \
		is_chevron.c \

OBJS = $(SRCS:.c=.o)

NAME = libft.a

RM = rm -f

CC = gcc

CFLAGS = -Wall -Wextra -Werror

$(NAME): $(OBJS)
	ar -crs $(NAME) $(OBJS)

all: $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: clean fclean re all
