NAME = minishell

CC = gcc

CFLAGS = -Wall -Wextra -Werror

CFLAGS += -g 
# CFLAGS += -fsanitize=address

MAIN = 	srcs/main.c			\
		srcs/init_struct.c	\
		srcs/free.c	\
		srcs/env.c			\
		srcs/parsing/parse.c \
		srcs/parsing/parse_utils.c \
		srcs/parsing/parse_quotes.c \
		srcs/parsing/parse_cmds.c \
		srcs/parsing/parse_files.c \
		srcs/exec/exec.c \
		srcs/exec/exec_process_child.c \
		srcs/exec/exec_process_brother.c \
		srcs/exec/exec_process_parent.c \
		srcs/exec/exec_utils.c \
		srcs/exec/exec_builtins.c \
		srcs/builtins/echo.c \
		srcs/builtins/cd.c \
		srcs/builtins/export.c \
		srcs/signals.c


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
