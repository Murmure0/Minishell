#include "../includes/minishell.h"

void	parse(void)
{
	char **nodes;

	/*  - on recupere l'input, puis on le split avec les pipes
			- check le 1er " ou '
			-	si on le trouve, on cherche a le matcher
			- 	sinon => erreur
			- on remplace toutes les variables $ sauf celles entre ''
			- 
			- on resplit chaque node obtenu avec espaces / tabs
			- 
		
	*/
	nodes = ft_split(g_shell.prompt, '|');
	if (!nodes)
		return ;
	
}