/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmasse <vmasse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 13:05:41 by mberthet          #+#    #+#             */
/*   Updated: 2022/01/12 14:21:26 by vmasse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft.h"
# include <stdio.h>

/* --Maillon des lst chainees des infiles/outfile--*/

typedef struct s_file
{
	int double_chevron;
	char *name;
	struct s_file *next;
}	t_file;

/* --Maillon de la lst chainée des commandes : un maillon = une commande, separateur de cmd : |-- */

typedef struct s_command
{
	struct s_file *infiles; //tout les infile precedents la cmd sont stockés la dedans dans 
	struct s_file *outfiles; // tous les outfile suivant la cmd 
	char **cmd; //la cmd du pipe actuel
	char **env;
	struct s_command *next; // la commande du prochain pipe
} 	t_command;

/* --Declaration de notre structure globale-- */


typedef struct s_shell
{
	char **env;
	char **path;
	char *line;
}	t_shell;

t_shell g_struct;

/* g_struct */ 
void    init_struct(t_shell *g_struct, char **env);

/* env */ 
char	*find_env_paths(char **envp);
char	**get_env_paths(char **envp);

/* main */ 


#endif