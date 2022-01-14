#include "../includes/minishell.h"

//Fonctions pour les lst chainees infile/outfile :

//Le maillon dans lequel est stocké un seul "mot" : < in  ou >> out
// t_file *newfile(int chevron, char *name)
// {
// 	t_file *new;

// 	new = malloc(sizeof(t_file));
// 	if (!new)
// 		return (NULL);
// 	new->double_chevron = chevron; //chevron simple : 1, chevron double : 2
// 	new->name = ft_strdup(name);
// 	if (!new->name)
// 		return(NULL); //erreur a gerer cornebidouille
// 	new->next = NULL;
// 	return(new);
// }

// //Generation de la lst chainee a partir du char * parsé d'infile ou d'outfile:
// t_file *creat_lst_file(int chevron, char *name)
// {
// 	t_file *first;
// 	t_file *tmp;

// 	first = newfile(chevron, name);
// 	if (!first)
// 		return (NULL);
// 	tmp = first;

// 	while () /* le char ** contenant les infiles ou celui des outfiles */
// 	{

// 		tmp->next = newfile(chevron, name);
// 		if (!tmp->next)
// 		{
// 			ft_lstclear(&tmp);
// 			return(NULL);
// 		}
// 		tmp = tmp->next;
// 	}
// 	tmp->next = NULL;
// 	return(first);
// }


// //Creation d'un chainon de la lst chainees des commandes, pour laquelle on associe les lst chainees d'infile/outfile precedement creees :
// t_command *new_cmd(t_file *lst_infiles, t_file *lst_outfiles, char ** cmd)
// {
// 	t_command *new;

// 	new = malloc(sizeof(t_command));
// 	if(!new)
// 		return (NULL);
// 	new->infiles = lst_infiles;
// 	new->outfiles = lst_outfiles;
// 	new->cmd = cmd;
// 	new->env = g_shell.env;
// 	return (new);
// }

// //Creation de la lst chainee des commandes, quand il y a des | :

// t_command *creat_lst_cmd(t_file *lst_infiles, t_file *lst_outfiles, char ** cmd)
// {
// 	t_command *first;
// 	t_command *tmp;
// 	int i;
// 	int n;

// 	i = -1;
// 	first = new_cmd(lst_infiles, lst_outfiles, cmd);
// 	if (!first)
// 		return(NULL);
// 	tmp = first;

// 	while (++i < n) /* le nb n de noeud = (nb de |)*/
// 	{
// 		tmp->next = new_cmd(lst_infiles, lst_outfiles, cmd);
// 		if (!tmp->next)
// 		{
// 			ft_lstclear(&tmp);
// 			return(NULL);
// 		}
// 		tmp = tmp->next;
// 	}
// 	tmp->next = NULL;
// 	return(first);
// }