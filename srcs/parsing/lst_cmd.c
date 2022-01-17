#include "../../includes/minishell.h"

//Fonctions pour les lst chainees infile/outfile :

//Le maillon dans lequel est stocké un seul "mot" : < in  ou >> out
t_token *new_token(int redir, char *name)
{
	t_token *new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->redir = redir; //chevron simple : 1, chevron double : 2
	new->name = ft_strdup(name);
	if (!new->name)
		return(NULL); //erreur a gerer cornebidouille
	new->next = NULL;
	return(new);
}

//Generation de la lst chainee a partir du char * parsé d'infile ou d'outfile:
t_token *create_lst_token(int chevron, char *name)
{
	t_token *first;
	t_token *tmp;

	first = new_token(chevron, name);
	if (!first)
		return (NULL);
	tmp = first;

	// while () /* le char ** contenant les infiles ou celui des outfiles */
	// {

	// 	tmp->next = newfile(chevron, name);
	// 	if (!tmp->next)
	// 	{
	// 		ft_lstclear(&tmp);
	// 		return(NULL);
	// 	}
	// 	tmp = tmp->next;
	// }
	tmp->next = NULL;
	return(first);
}


//Creation d'un chainon de la lst chainees des commandes, pour laquelle on associe les lst chainees d'infile/outfile precedement creees :
t_node *new_node(t_token *lst_infiles, t_token *lst_outfiles, char **cmd)
{
	t_node *new;

	new = malloc(sizeof(t_node));
	if(!new)
		return (NULL);
	new->infiles = lst_infiles;
	new->outfiles = lst_outfiles;
	new->cmd = cmd;
	new->env = g_shell.env;
	return (new);
}

//Creation de la lst chainee des commandes, quand il y a des | :

t_node *create_lst_node(t_token *lst_infiles, t_token *lst_outfiles, char **node)
{
	t_node *first;
	t_node *tmp;
	int i;
	int n;

	i = -1;
	first = new_node(lst_infiles, lst_outfiles, node);
	if (!first)
		return(NULL);
	tmp = first;
	n = 0;
	while (++i < n) /* le nb n de noeud = (nb de |)*/
	{
		tmp->next = new_node(lst_infiles, lst_outfiles, node);
		if (!tmp->next)
		{
			// ft_lstclear(&tmp);
			return(NULL);
		}
		tmp = tmp->next;
	}
	tmp->next = NULL;
	return(first);
}