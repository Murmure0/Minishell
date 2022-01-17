#include "../../includes/minishell.h"

//Fonctions pour les lst chainees infile/outfile :

//Le maillon dans lequel est stocké un seul "mot" : < in  ou >> out
t_token *new_token(t_parsing *parstruct, int redir, char *name)
{
	t_token *new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->redir = redir; //chevron simple : 1, chevron double : 2
	new->name = ft_strdup(name);
	if (!new->name)
		return(NULL); //erreur a gerer cornebidouille
	if (redir == 1)
		parstruct->head_infiles = new;
	else if (redir == 2 || redir == 3)
		parstruct->head_outfiles = new;
	new->next = NULL;
	return(new);
}

void	token_add_back(t_parsing *parstruct, t_token **token, int redir, char *name)
{
	t_token	*p;

	if (!token)
		return ;
	// if (!*token)
	// 	*token = new_token(parstruct, redir, name);
	// else
	// {

	p = *token;
	while (p->next)
		p = p->next;
	p->next = new_token(parstruct, redir, name);
	
	// }
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
	new->cmd = cmd; // faire une copie
	return (new);
}

//Creation de la lst chainee des commandes, quand il y a des | :

t_node *create_lst_node(t_token *lst_infiles, t_token *lst_outfiles, char **node, int pipe_nb)
{
	t_node *first;
	t_node *tmp;
	int i;

	i = -1;
	first = new_node(lst_infiles, lst_outfiles, node);
	if (!first)
		return(NULL);
	tmp = first;
	while (++i < pipe_nb) /* le nb n de noeud = (nb de |)*/
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