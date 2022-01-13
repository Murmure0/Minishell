#include "../includes/minishell.h"

int	arr_len(char **s)
{
	int	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

char	*check_quotes(char **to_replace)
{

	return (NULL);
}

void	parse(void)
{
	char **nodes;
	char **to_replace;

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
	to_replace = malloc(sizeof(char *) * arr_len(nodes));
	if (!to_replace)
		ft_exit();
	while (nodes && *nodes)
	{
		// printf("%s\n", *nodes);
		*to_replace = check_quotes(*nodes);
		to_replace++;
		nodes++;
	}
}