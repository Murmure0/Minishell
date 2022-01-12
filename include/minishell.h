/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 13:05:41 by mberthet          #+#    #+#             */
/*   Updated: 2022/01/12 16:13:06 by mberthet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/errno.h>

#ifndef MINISHELL_H
# define MINISHELL_H
#endif


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
} t_command;

/* --Declaration de notre structure globale-- */


typedef struct s_shell
{
	char **env;
	char **path;
	char *line;
}		t_shell;

struct s_shell g_struct;

