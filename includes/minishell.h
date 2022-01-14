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

/* --Maillon des lst chainees des infiles/outfile--*/

typedef struct s_file
{
	int double_chevron; // 0 si simple ou double <, 1 si double et >
	char *name;
	struct s_file *next;
}	t_file;

/* --Maillon de la lst chainée des commandes : un maillon = une commande, separateur de cmd : |-- */

typedef struct s_command
{
	t_file *infiles; //tout les infile precedents la cmd sont stockés la dedans dans 
	t_file *outfiles; // tous les outfile suivant la cmd 
	char **cmd; //la cmd du pipe actuel
	char **env;
	struct s_command *next; // la commande du prochain pipe
} 	t_command;

/* Parsing */

typedef struct s_parsing
{
	char	**nodes; // ensemble des noeuds split par |

	int	inhib; // 0 si cest double, 1 si simple
	int	d_quotes_nb;
	int	s_quotes_nb;
	int	*pos_d_quotes; // array of pos to match "
	int	*pos_s_quotes; // array of pos to match '
}	t_parsing;

/* --Declaration de notre structure globale-- */


typedef struct s_shell
{
	char **env;
	char **path;
	char *prompt;
}	t_shell;

t_shell g_shell;

/* g_shell */ 
void    init_struct(t_shell *g_shell, char **env);

/* env */ 
char	*find_env_paths(char **envp);
char	**get_env_paths(char **envp);
char	**get_env(char **env);

/* main */ 
void	ft_free(void);
void	ft_exit(void);

/* main */ 
void	parse(void);

#endif