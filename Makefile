NAME = minishell

CC = gcc

CFLAGS = -Wall -Wextra -Werror -I/Users/$(USER)/.brew/opt/readline/include

CFLAGS += -g 
# CFLAGS += -fsanitize=address

MAIN = 	srcs/main.c			\
		srcs/init_struct.c	\
		srcs/init_struct_utils.c	\
		srcs/free.c	\
		srcs/utils.c	\
		srcs/env/env.c			\
		srcs/env/env_utils.c			\
		srcs/env/shlvl.c			\
		srcs/parsing/parse.c \
		srcs/parsing/parse_utils.c \
		srcs/parsing/parse_quotes.c \
		srcs/parsing/parse_cmds.c \
		srcs/parsing/parse_cmds_utils.c \
		srcs/parsing/parse_files.c \
		srcs/parsing/parse_dollar.c \
		srcs/parsing/parse_dollar_utils.c \
		srcs/parsing/ft_split_pipe.c \
		srcs/parsing/ft_split_utils.c \
		srcs/parsing/remove_quotes.c \
		srcs/parsing/remove_quotes_utils.c \
		srcs/parsing/files_expander.c \
		srcs/parsing/set_quotes.c \
		srcs/parsing/set_quotes_two.c \
		srcs/exec/parse_heredoc.c \
		srcs/exec/parse_heredoc_del.c \
		srcs/exec/gnl.c \
		srcs/exec/exec.c \
		srcs/exec/exec_process_child.c \
		srcs/exec/exec_process_child_fd.c \
		srcs/exec/exec_process_brother.c \
		srcs/exec/exec_process_brother_fd.c \
		srcs/exec/exec_process_parent.c \
		srcs/exec/exec_process_parent_fd.c \
		srcs/exec/exec_utils.c \
		srcs/exec/exec_builtins.c \
		srcs/exec/exec_builtins_redir.c \
		srcs/builtins/echo.c \
		srcs/builtins/cd.c \
		srcs/builtins/export.c \
		srcs/builtins/unset.c \
		srcs/builtins/pwd.c \
		srcs/builtins/exit.c \
		srcs/builtins/env.c \
		srcs/builtins/builtins_utils.c \
		srcs/signals.c

SOURCES = $(MAIN)

LIBFT = ./libft/libft.a

OBJECTS = $(SOURCES:.c=.o)

all : $(NAME)

$(NAME): $(LIBFT) $(OBJECTS)
	@$(CC) $(CFLAGS) $(OBJECTS) -L./libft -lft -lreadline -L/Users/$(USER)/.brew/opt/readline/lib -o $(NAME)

$(LIBFT):
	$(MAKE) -C ./libft

clean:
	/bin/rm -f $(OBJECTS) && cd ./libft/ && make clean
	
fclean: clean
	/bin/rm -f $(NAME) && cd ./libft/ && make fclean
	
re: fclean all

.PHONY: clean fclean re all
