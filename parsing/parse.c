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
			- ajout du chevron + filename dans un char **
			- creation de la liste chainee
			- ajout du chevron + filename dans un char **
		
	*/

	nodes = ft_split(g_shell.prompt, '|');
	// savoir ce qui a dans nodes sans pipes
	if (!nodes)
		ft_exit();

	while (nodes)
	{
		printf("%s\n", *nodes);
		nodes++;
	}
}