#ifndef MINISHELL_H
# define MINISHELL_H

/* ! faire le tri a la fin dans les differents headers pour ne pas avoir de doublons*/

# include "./libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/errno.h>
# include <stdio.h>
# include <readline/readline.h>

# define no_redir	0
# define redir_l	1
# define redir_r_s	2
# define redir_r_d	3

typedef struct s_token
{
	int 	redir; // 0 si no redir, 1 si simple <, 2 si >, 3 si >>
	int		pos;
	char 	*name;
}	t_token;

typedef struct s_node
{
    t_token     *infiles; 
    t_token     *outfiles;
    t_token     *cmd;
}     t_node;

typedef struct s_parsing
{
	char 	*prompt;
	char	**nodes;
	char	chevron;
	int		pipe_nb;
}	t_parsing;

typedef struct s_shell
{
	char **env;
	char **path;
}	t_shell;

/* ------------------------------------ init_struct.c ------------------------------------ */
void    init_struct(t_shell *g_shell, char **env);

/* ------------------------------------ env.c -------------------------------------------- */
char	*find_env_paths(char **envp);
char	**get_env_paths(char **envp);
char	**get_env(char **env);

/* ------------------------------------ main.c -------------------------------------------- */
void	ft_free(t_shell shell);
void	ft_exit(t_shell shell);

/* --------------------------------------------------------------------------------- */
/* ------------------------------------ PARSING ------------------------------------ */
/* --------------------------------------------------------------------------------- */

/* ------------------------------------ parse.c ------------------------------------ */
void	parse(t_node *node, t_parsing *parstruct);
// void	tokenize(t_node *node, t_parsing *parstruct, char *raw_node);
int		get_tokens_nb(char *node);
void	add_files_redir(t_node *nodes, t_parsing *ps);
char	*get_file_name(t_node *node, char *raw_node, int *j);
void	add_file(t_node *node, char *raw_node, int redir, int *j);

/* ------------------------------------ parse_quotes.c ------------------------------ */
int		get_quote_pos(t_parsing *parstruct, int start);
int		get_matching_quote_pos(t_parsing *parstruct, int start);
void	check_quotes_for_pipe_split(t_parsing *parstruct);

/* ------------------------------------ lst_cmd.c ----------------------------------- */
t_token *new_token(t_parsing *parstruct, int redir, char *name);
void	token_add_back(t_parsing *parstruct, t_token **token, int redir, char *name);
t_node *new_node(t_token *lst_infiles, t_token *lst_outfiles, char **node);
t_node *create_lst_node(t_token *lst_infiles, t_token *lst_outfiles, char **node, int pipe_nb);

/* --------------------------------------------------------------------------------- */
/* ------------------------------------ EXEC --------------------------------------- */
/* --------------------------------------------------------------------------------- */

/* ------------------------------------ exec_clean.c ------------------------------- */
int		exec(t_node *node, t_shell g_shell);
void	child_process(pid_t child_pid/*, int fd_in*/, t_node *node/*, int *fds*/, t_shell t_shell);

/* ------------------------------------ exec_lst.c ------------------------------- */
int		find_fd_in(t_node *node);

/* --------------------------------------------------------------------------------- */
/* ------------------------------------ BUILTINS ----------------------------------- */
/* --------------------------------------------------------------------------------- */

//int echo(char **str);
#endif