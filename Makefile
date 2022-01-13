NAME = minishell

CC = gcc

CFLAGS = -Wall -Wextra -Werror
# CFLAGS += -g

MAIN = 	srcs/main.c			\
		srcs/init_struct.c	\
		srcs/env.c			\
		./exec/exec.c \
		./exec/here_doc.c \
		./exec/lst_cmd.c \
		./parsing/parse.c \

SOURCES = $(MAIN)

LIBFT = ./libft/libft.a

OBJECTS = $(SOURCES:.c=.o)

all : $(NAME)

$(NAME): $(LIBFT) $(OBJECTS)
	@$(CC) $(CFLAGS) $(OBJECTS) -L./libft -lft -lreadline -o $(NAME)

$(LIBFT):
	$(MAKE) -C ./libft

clean:
	/bin/rm -f $(OBJECTS) && cd ./libft/ && make clean
	
fclean: clean
	/bin/rm -f $(NAME) && cd ./libft/ && make fclean
	
re: fclean all

.PHONY: clean fclean re all