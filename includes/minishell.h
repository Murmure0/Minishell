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
# include <readline/history.h>
// # include <wait.h>

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
    char		**cmd;
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

typedef struct s_exec
{
	int	fd_in;
	int	fd_out; //si plusieurs cmd fd_out = fds;
}	t_exec;

/* ------------------------------------ init_struct.c ------------------------------------ */
void    init_struct(t_shell *g_shell, char **env);

/* ------------------------------------ env.c -------------------------------------------- */
char	*find_env_paths(char **envp);
char	**get_env_paths(char **envp);
char	**get_env(char **env);

/* ------------------------------------ main.c -------------------------------------------- */
int		ret_err(int ret, char *msg);
void	final_free(t_shell *sh, t_parsing *ps, t_node *n);

/* --------------------------------------------------------------------------------- */
/* ------------------------------------ PARSING ------------------------------------ */
/* --------------------------------------------------------------------------------- */

/* ------------------------------------ parse.c ------------------------------------ */
t_node	*parse(t_node *node, t_parsing *parstruct);
int		get_tokens_nb(char *node);
void	add_files_redir(t_node *nodes, t_parsing *ps);
char	*get_file_name(t_node *node, char *raw_node, int *j);
void	add_file(t_node *node, char *raw_node, int redir, int *j);

/* ------------------------------------ parse_quotes.c ------------------------------ */
int		get_quote_pos(t_parsing *parstruct, int start);
int		get_matching_quote_pos(t_parsing *parstruct, int start);
int		check_quotes_for_pipe_split(t_parsing *parstruct);

/* ------------------------------------ lst_cmd.c ----------------------------------- */
t_token *new_token(t_parsing *parstruct, int redir, char *name);
void	token_add_back(t_parsing *parstruct, t_token **token, int redir, char *name);
t_node *new_node(t_token *lst_infiles, t_token *lst_outfiles, char **node);
t_node *create_lst_node(t_token *lst_infiles, t_token *lst_outfiles, char **node, int pipe_nb);

/* --------------------------------------------------------------------------------- */
/* ------------------------------------ EXEC --------------------------------------- */
/* --------------------------------------------------------------------------------- */

/* ------------------------------------ exec.c ------------------------------- */
int		exec(t_node *node, t_shell g_shell);

/* ------------------------------------ exec_utils.c ------------------------------- */
int		path_finder(t_node *first_node, t_shell shell);
int		exec_cmd(t_node *first_node, t_shell shell);
void	free_all(t_node *first_node, t_shell shell);

/* ---------------------------------- exec_process_child.c ------------------------- */
void	child_process(pid_t child_pid, t_exec *exec_st, t_node *first_node, t_shell shell);
int		find_fd_in(t_node *first_node);
int		find_fd_out(t_node *first_node);
t_exec	*init_exec_st(t_node *first_node);
/* --------------------------------------------------------------------------------- */
/* ------------------------------------ BUILTINS ----------------------------------- */
/* --------------------------------------------------------------------------------- */

int echo(char **str);

#endif