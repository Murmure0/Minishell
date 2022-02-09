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
# include <dirent.h>
# include <wait.h>

# define no_redir	0
# define redir_l	1
# define redir_r_s	2
# define redir_r_d	3

typedef struct s_node
{
    char     *infiles;
    char     *outfiles;
	int		 append;
	int		 invalid_infile;
    char	**cmd;
	int		node_nb;
}     t_node;

typedef struct s_parsing
{
	int		i;
	int		j;
	int		pos_infiles;
	int		pos_outfiles;
	int		pos_cmd;
	char 	*prompt;
	char	**nodes;
	char	chevron;
	int		pipe_nb;
	int		cmd_nb;
	int		stop_err;
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
	int pfd_out;
	int pfd_in;
}	t_exec;

/* ------------------------------------ init_struct.c ------------------------------------ */
void    init_struct(t_shell *g_shell, char **env);

/* ------------------------------------ env.c -------------------------------------------- */
char	*find_env_paths(char **envp);
char	**get_env_paths(char **envp);
char	**get_env(char **env);
char 	**add_slash(char **env_paths);
void 	free_tab(char **env_paths);

char	**realloc_env(char **env);
char	**update_env_var(char **env, char *str, char *new);
char	**add_env_var(char **env, char *var);

/* ------------------------------------ main.c -------------------------------------------- */
int		ret_err(int ret, char *msg);
void	final_free(t_shell *sh, t_parsing *ps, t_node *n);

/* --------------------------------------------------------------------------------- */
/* ------------------------------------ PARSING ------------------------------------ */
/* --------------------------------------------------------------------------------- */

/* ------------------------------------ parse.c ------------------------------------ */
int		init_global_struct(t_parsing *ps);
int		init_local_struct(t_node **nodes, t_parsing **ps);
int		process_parse(t_node **nodes, t_parsing *ps);
t_node	*parse(t_parsing *parstruct);

int	check_space_between_redirs(t_parsing *ps);


/* ------------------------------------ parse_utils.c ------------------------------- */
int		arr_len(char **arr);
char	*str_slice(char *src, int start, int stop);
void	skip_spaces(t_parsing *ps);

/* ------------------------------------ parse_files.c ------------------------------ */
int		get_files_nb(char *node, char chevron);
char	*get_file_name(t_parsing *ps, t_node *nodes, int redir);
int		add_file(t_node *nodes, t_parsing *ps, int redir);

/* ------------------------------------ parse_cmds.c ------------------------------ */
int		process_get_cmds_nb(char *node, int i, int *nb);
int		get_cmds_nb(char *node);
void	add_command_args(t_node **nodes, t_parsing *ps);
void	add_command(t_node **nodes, t_parsing *ps);

/* ------------------------------------ parse_quotes.c ------------------------------ */
int		get_quote_pos(t_parsing *parstruct, int start);
int		get_matching_quote_pos(t_parsing *parstruct, int start);
int		check_quotes_for_pipe_split(t_parsing *parstruct);

/* --------------------------------------------------------------------------------- */
/* ------------------------------------ EXEC --------------------------------------- */
/* --------------------------------------------------------------------------------- */

/* ------------------------------------ exec.c ------------------------------- */
int		exec(t_node *node, t_shell *shell);

/* ------------------------------------ exec_utils.c ------------------------------- */
int		path_finder(t_node *first_node, t_shell shell);
int		exec_cmd(t_node *first_node, t_shell shell);
void	free_all(t_node *first_node, t_shell shell);
int		find_builtin(t_node *first_node, t_shell *shell);


/* ---------------------------------- exec_process_child.c ------------------------- */
void	child_process(pid_t child_pid, t_exec *exec_st, t_node *first_node, t_shell *shell);
int		find_fd_in(t_node *first_node);
int		find_fd_out(t_node *first_node, t_exec *exec_st);
t_exec	*init_exec_st(t_node *first_node);

/* ---------------------------------- exec_process_parent.c ------------------------- */
void parent_process(pid_t child_pid, t_exec *exec_st, t_node *second_node, t_shell *shell);

/* --------------------------------------------------------------------------------- */
/* ------------------------------------ BUILTINS ----------------------------------- */
/* --------------------------------------------------------------------------------- */

int 	my_echo(char **str);
int		my_cd(t_shell *shell, char *dir);
int		my_export(t_shell *shell, char **var);

#endif
