/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 17:16:17 by vmasse            #+#    #+#             */
/*   Updated: 2022/03/15 08:30:26 by mberthet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/errno.h>
# include <sys/types.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>
# include <signal.h>
# include <errno.h>
# include <termios.h>

//# include <wait.h>

/* ERROR MESSAGES */

# define PERR			"minishell: "
# define NO_FILE	"minishell: syntax error near unexpected symbol « newline »"
# define HOME_UNSET	"minishell: cd: « HOME » not set"

typedef struct s_node
{
	int		infile_hd;
	int		in_id;
	int		invalid_infile;
	int		node_nb;
	int		append;
	int		cmd_nb;
	char	*infiles;
	char	*outfiles;
	char	**cmd;
}			t_node;

typedef struct s_parsing
{
	int		i;
	int		j;
	int		k;
	int		pos_infiles;
	int		pos_outfiles;
	int		pos_cmd;
	int		pipe_nb;
	int		cmd_nb;
	int		stop_err;
	int		pos_tmp;
	int		is_s_quote;
	int		is_d_quote;
	char	quote;
	char	chevron;
	char	*prompt;
	char	**nodes;
}	t_parsing;

typedef struct s_shell
{
	char			**env;
	char			**path;
	struct termios	termios_p;
}				t_shell;

typedef struct s_exec
{
	int	fd_in;
	int	fd_out;
	int	pfd_out;
	int	pfd_in;
	int	num_cmd;
}				t_exec;

typedef struct s_split
{
	int	i;
	int	j;
	int	k;
	int	is_quote;
}	t_split;

/* -------------------------- init_struct.c ----------------------- */
void	init_shell_struct(t_shell *shell, char **env);
int		init_global_struct(t_parsing *ps, t_shell *sh);
void	init_nodestruct(t_node **nodes, t_parsing **ps, t_shell *sh);
void	init_local_struct(t_node **nodes, t_parsing **ps, t_shell *sh);

/* -------------------------- init_struct_utils.c ----------------------- */
int		check_empty_before_pipe(char *s);
int		check_empty_pipe(t_parsing *ps);

/* ---------------------------- utils.c ------------------------------------ */
int		ret_err(int ret, char *msg);
void	ft_exit(t_shell *sh, t_parsing *ps, t_node *n, char *err);
int		not_emptycmd(char *cmd);

/* ---------------------------- free.c ------------------------------------ */
void	free_parstruct(t_parsing *ps);
void	free_shellstruct(t_shell *sh);
void	free_nodestruct(t_node *n, t_parsing *ps);
void	final_free(t_shell *sh, t_parsing *ps, t_node *n);

/* ---------------------------- signals.c ---------------------------- */
void	handle_signal(int sig);
void	handle_sig_fork(int sig);
void	handle_sig_heredoc(int sig);

/* ---------------------------- gnl.c --------------------------------- */
char	*get_next_line(int fd);

/* ----------------------------------------------------------------- */
/* ---------------------------- ENV -------------------------------- */
/* ----------------------------------------------------------------- */

/* ---------------------------- env.c ------------------------------------ */
char	*find_env_paths(char **envp);
char	**get_env_paths(char **envp);
char	**get_env(char **env);
char	**add_slash(char **env_paths);
void	free_tab(char **env_paths);

/* ---------------------------- env_utils.c ------------------------- */
char	**realloc_env_cpy_env(char **env_cpy);
char	**realloc_env(char **env);
char	**update_env_var(char **env, char *str, char *new);
char	**add_env_var(char **env, char *var);
char	*get_env_var_value(char **env, char *key);

/* ---------------------------- shlvl.c --------------------------- */
char	*update_shell_lvl(char *env);

/* ----------------------------------------------------------------- */
/* ---------------------------- PARSING ---------------------------- */
/* ----------------------------------------------------------------- */

/* ---------------------------- parse.c ---------------------------- */
int		parse_case_infile(t_node *nodes, t_parsing *ps, t_shell *sh);
int		parse_case_outfile(t_node *nodes, t_parsing *ps, t_shell *sh);
int		process_parse(t_node **nodes, t_parsing *ps, t_shell *sh);
t_node	*parse(t_parsing *ps, t_shell *sh);

/* ---------------------------- parse_utils.c ----------------------- */
int		arr_len(char **arr);
int		check_space_between_redirs(t_parsing *ps);
void	skip_spaces(t_parsing *ps);
void	modify_dollar_value(t_parsing *ps, t_shell *sh);
void	init_quote_states(t_parsing *ps);
void	end_parse(t_parsing *ps, t_node *nodes, t_shell *sh);

/* ---------------------------- parse_files.c ---------------------- */
int		get_files_nb(char *node, char chevron);
char	*get_file_name(t_parsing *ps, t_node *nodes, int redir);
void	add_infile(t_node *nodes, t_parsing *ps, t_shell *sh);
int		add_outfile(t_node *nodes, t_parsing *ps, int redir, t_shell *sh);
int		add_file(t_node *nodes, t_parsing *ps, int redir, t_shell *sh);

/* ---------------------------- parse_cmds.c ---------------------- */
int		check_for_command_args(t_parsing *ps, int *pos_start, int *stop);
int		add_cmd_args_case_stop(t_parsing *ps, t_node **n, t_shell *sh, int pos);
void	add_command_args(t_node **nodes, t_parsing *ps, t_shell *sh);
void	add_command(t_node **nodes, t_parsing *ps, t_shell *sh);

/* ---------------------------- parse_cmds_utils.c ---------------------- */
void	set_quotes_for_prompt(t_parsing *ps);
void	get_cmds_nb_case_chevron(char *node, int *i, t_parsing *ps);
int		get_cmds_nb(t_parsing *ps, char *node);

/* ---------------------------- parse_quotes.c ---------------------- */
int		get_quote_pos(t_parsing *parstruct, int start);
int		get_matching_quote_pos(t_parsing *parstruct, int start);
int		check_quotes_for_pipe_split(t_parsing *parstruct);
int		get_next_quote(t_parsing *ps, char *s, int pos);

/* ---------------------------- remove_quotes.c ---------------------- */
char	*remove_quote(char *s, int pos);
void	remove_quotes_cmd(t_node *nodes, t_parsing *ps);
void	set_quotes_for_cmd_in_quote(t_parsing *ps, t_node *n);
void	set_quotes_for_files_in_quote(t_parsing *ps,
			char *file, int *count_s, int *count_d);
char	*remove_quotes_files(t_parsing *ps, char *file);

/* ---------------------------- remove_quotes_utils.c ---------------------- */
int		is_removable(t_parsing *ps, char *file, int count_d, int count_s);
void	init_var_rm_quotes_files(t_parsing *ps, int *s, int *d);
void	increment_quotes_count(char c, int *d, int *s);
int		gnq_rm_quotes_files(int *pos_quote, t_parsing *ps, char *file);
char	*end_rm_quotes_files(t_parsing *ps, char *file);

/* ---------------------------- set_quotes.c ---------------------- */
void	set_quotes(t_parsing *ps, char *n, int *i);
void	set_quotes_without_move(t_parsing *ps, char *n, int i);
int		is_quote(char c);

/* ---------------------------- set_quotes_two.c ---------------------- */
void	set_quotes_for_getfilename(t_parsing *ps,
			int j, int *count_s, int *count_d);
void	set_quotes_for_cmd_in_quote(t_parsing *ps, t_node *n);
void	set_quotes_for_files_in_quote(t_parsing *ps,
			char *file, int *count_s, int *count_d);
void	set_quotes_for_prompt(t_parsing *ps);

/* ---------------------------- files_expander.c ---------------------- */
void	skip_spaces_local(t_parsing *ps, int *j);
void	set_quotes_for_files(t_parsing *ps, int *j);
void	replace_dollar_files(t_node *n, t_parsing *ps, t_shell *sh, int *pos);
void	expand_dollar_files(t_node *nodes, t_parsing *ps, t_shell *sh);

/* ---------------------------- parse_dollar.c ---------------------- */
int		get_next_dollar(char *s, int pos);
void	expand_dollar_value_cmd(t_node *nodes, t_parsing *ps, t_shell *sh);
void	replace_dollar(t_node *n, t_parsing *ps, t_shell *sh, int *pos);
void	set_quotes_for_cmd(t_parsing *ps, t_node *n);
void	replace_exit_st_cmd(t_node *n, t_parsing *ps, t_shell *sh, int *pos);

/* ---------------------------- parse_dollar_utils.c ---------------------- */
void	free_value_tmp(char *value, char *tmp);
int		get_key_len(char *s, int pos);

/* ---------------------------- parse_heredoc.c ---------------------- */
int		add_heredoc_file(t_node *nodes, t_parsing *ps);
int		parse_case_hd(t_node *nodes, t_parsing *ps);

/* ---------------------------- parse_heredoc_del.c ---------------------- */
int		check_hd_content(t_parsing *ps);
char	*get_delimiter(t_parsing *ps);

/* ---------------------------- ft_split_pipe.c ---------------------- */
char	**ft_split_pipe(char const *s, char c, t_parsing *ps);
void	set_quote(char c, t_split *st);
void	init_struct(t_split *st);
int		check_end(t_split *st, char const *s, char **arr);
void	set_quote_utils(char c, t_split *st);

/* ---------------------------- ft_split_pipe.c ---------------------- */
char	*replace_in_str(char *s, char *value, int pos, int len);

/* ----------------------------------------------------------------- */
/* ---------------------------- EXEC ------------------------------- */
/* ----------------------------------------------------------------- */

/* ---------------------------- exec.c -------------------------- */
int		exec(t_node *node, t_shell *shell);

/* ---------------------------- exec_utils.c ----------------------- */
t_exec	*init_exec_st(t_node *first_node);
int		path_finder(t_node *first_node, t_shell *shell);
int		exec_cmd(t_node *first_node, t_shell *shell);
void	free_all(t_node *first_node, t_shell *shell);
void	fd_dup(int fd, int std);

/* -------------------------- exec_process_child.c ----------------- */
int		find_fd_in(t_node *first_node);
int		find_fd_out(t_node *first_node, t_exec *exec_st);
int		exec_child_proc(t_node *first_node, t_shell *shell, t_exec *exec_st);

/* -------------------------- exec_process_parent.c ----------------- */
int		parent_process(t_exec *prev_exec_st, t_node *last_node, t_shell *shell);

/* -------------------------- exec_process_parent_fd.c ----------------- */
int		find_fd_in_parent(t_node *last_node, t_exec *exec_st);

/* -------------------------- exec_process_brother_fd.c ----------------- */
t_exec	*init_exec_st_bro(t_node *middle_node, t_exec *prev_exec_st);
int		find_fd_out_parent(t_node *last_node);
t_exec	*init_exec_st_parent(t_node *last_node, t_exec *exec_st);

/* -------------------------- exec_process_brother.c ----------------- */
int		brother_process(t_exec *prev_exec_st, t_node *middle_node,
			t_shell *shell);

/* ---------------------------- exec_builtins_redir.c ----------------------- */
int		redir_solo_builtin(t_node *first_node, t_shell *shell,
			t_exec	*exec_st);

/* ---------------------------- exec_builtins.c ----------------------- */
int		find_builtin(t_node *first_node, t_shell *shell, char exec);

/* ----------------------------------------------------------------- */
/* ---------------------------- BUILTINS --------------------------- */
/* ----------------------------------------------------------------- */
int		my_echo(char **str);
int		my_cd(t_shell *shell, char *dir);
int		my_export(t_shell *shell, char **var);
int		my_unset(t_shell *sh, char **var);
int		my_env(t_shell *sh, t_node *first_node);
int		my_exit(t_node *first_node);
int		my_pwd(void);
char	*get_var_value(char *cmd);
char	*get_var_key(char *cmd);
int		get_equal(char *s);
void	free_get_pwd(char **pwd);
int		get_pwds_inside(t_shell *s, char **home, char **pwd, int *add_home);

/* -------------------------- builtins_utils.c ------------------*/
void	free_export(char *key, char *value);
int		get_key_value_export(char **key, char **value, char *cmd);
int		create_oldpwd(t_shell *sh, int add_old, char *pwd);
void	init_update_env_vars(int *i, int *add_old);

/* -------------------------- main_utils.c ------------------*/
void	process_readline_inside(t_parsing *ps, t_node *nodes, t_shell *shell);

#endif
