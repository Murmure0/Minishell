#include "../includes/minishell.h"

int	arr_len(char **s)
{
	int	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

int	get_quotes_nb(char c)
{
	int	i;
	int	quotes_nb;

	i = -1;
	quotes_nb = 0;
	while (g_shell.prompt[++i])
	{
		if (g_shell.prompt[i] == c)
			quotes_nb++;
	}
	return (quotes_nb);
}

void	parse_quotes(t_parsing *parstruct)
{
	int	i;
	int	pos;

	// but = preparer pour le remplacement des $var
	i = 0;
	pos = 0;
	parstruct->d_quotes_nb = get_quotes_nb('"');
	parstruct->s_quotes_nb = get_quotes_nb('\'');
	if (parstruct->d_quotes_nb > 0)
	{
		parstruct->pos_d_quotes = malloc(sizeof(int) * parstruct->d_quotes_nb);
		if (!parstruct->pos_d_quotes)
			ft_exit();
	}
	if (parstruct->s_quotes_nb > 0)
	{
		parstruct->pos_s_quotes = malloc(sizeof(int) * parstruct->s_quotes_nb);
		if (!parstruct->pos_s_quotes)
			ft_exit();
	}
	if (!parstruct->d_quotes_nb && !parstruct->s_quotes_nb)
		return ;
	while (g_shell.prompt && g_shell.prompt[i])
	{
		if (g_shell.prompt[i++] == '"')
		{
			while (g_shell.prompt[i] != '"')
				i++;
			if (!g_shell.prompt[i])
				ft_exit(); // on est arrive a la fin, le " ne matche pas, erreur
			else
				parstruct->pos_d_quotes[pos++] = i;
		}
	}
}

void	parse(void)
{
	t_parsing	parstruct;

	/*  - on recupere l'input
			- check le 1er " ou '
			-	si on le trouve, on cherche a le matcher
			- 	sinon => erreur
			- on remplace toutes les variables $ sauf celles entre ''
			- puis on split avec les pipes pour creer les nodes
			- ajout du chevron + filename dans un char **
			- creation de la liste chainee

		- si on a double chevron, creation du fichier temp dans le parsing, et ajout dans
			la liste chainee des infiles avec 0	
	*/
	parse_quotes(&parstruct);
	parstruct.nodes = ft_split(g_shell.prompt, '|');
	if (!parstruct.nodes)
		ft_exit();
	while (parstruct.nodes && *parstruct.nodes)
	{
		printf("%s\n", *parstruct.nodes);
		parstruct.nodes++;
	}
}