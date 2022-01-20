NAME = minishell

CC = gcc

CFLAGS = -Wall -Wextra 

CFLAGS += -g -fsanitize=address
# 
MAIN = 	srcs/main.c			\
		srcs/init_struct.c	\
		srcs/env.c			\
		srcs/exec/pars_heredoc.c \
		srcs/parsing/parse.c \
		srcs/parsing/parse_quotes.c \
		srcs/exec/exec.c \
		srcs/exec/exec_lst.c \


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
