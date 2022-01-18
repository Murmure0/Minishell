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

/* --Maillon des lst chainees des infiles/outfile--*/

typedef struct s_token
{
	int redir; // 0 si no redir, 1 si simple <, 2 si >, 3 si >>
	char *name;
	struct s_token *next;
}	t_token;

/* --Maillon de la lst chainée des commandes : un maillon = une commande, separateur de cmd : |-- */

typedef struct s_node
{
	t_token *infiles; //tout les infile precedents la cmd sont stockés la dedans dans 
	t_token *outfiles; // tous les outfile suivant la cmd 
	char **cmd; //la cmd du pipe actuel
	struct s_node *next; // la commande du prochain pipe
} 	t_node;

/* Parsing */

typedef struct s_parsing
{
	t_token	*head_infiles;
	t_token	*head_outfiles;
	char 	*prompt;
	char	**nodes; // ensemble des noeuds split par |
	char	chevron;
	int		pipe_nb;
}	t_parsing;

/* --Declaration de notre structure globale-- */

typedef struct s_shell
{
	char **env;
	char **path;
}	t_shell;

t_shell g_shell;

/* ------------------------------------ init_struct.c ------------------------------------ */
void    init_struct(t_shell *g_shell, char **env);

/* ------------------------------------ env.c -------------------------------------------- */
char	*find_env_paths(char **envp);
char	**get_env_paths(char **envp);
char	**get_env(char **env);

/* ------------------------------------ main.c -------------------------------------------- */
void	ft_free(void);
void	ft_exit(void);

/* --------------------------------------------------------------------------------- */
/* ------------------------------------ PARSING ------------------------------------ */
/* --------------------------------------------------------------------------------- */

/* ------------------------------------ parse.c ------------------------------------ */
//void	parse(t_parsing *parstruct); //modif
t_node	*parse(t_parsing *parstruct); //
//void	tokenize(t_node *first_node, t_parsing *parstruct, char *raw_node);
t_node	*tokenize(t_parsing *parstruct, char *raw_node);

/* ------------------------------------ parse_quotes.c ------------------------------ */
int		get_quote_pos(t_parsing *parstruct, int start);
int		get_matching_quote_pos(t_parsing *parstruct, int start);
void	check_quotes_for_pipe_split(t_parsing *parstruct);

/* ------------------------------------ lst_cmd.c ----------------------------------- */
t_token *new_token(t_parsing *parstruct, int redir, char *name);
void	token_add_back(t_parsing *parstruct, t_token **token, int redir, char *name);
t_node *new_node(t_token *lst_infiles, t_token *lst_outfiles, char **node);
t_node *create_lst_node(t_token *lst_infiles, t_token *lst_outfiles, char **node, int pipe_nb);

#endif