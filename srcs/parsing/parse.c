#include "../../includes/minishell.h"

int	arr_len(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		i++;
	}
	return (i);
}

char	*ft_slice(char *src, int start, int stop)
{
	char	*string;
	int		src_size;
	int		i;

	if (!src)
		return (NULL);
	src_size = stop - start;
	string = malloc(sizeof(char) * (src_size + 1));
	if (!string)
		return (NULL);
	i = 0;
	while (start < stop)
	{
		string[i] = src[start];
		i++;
		start++;
	}
	string[src_size] = '\0';
	return (string);
}

int	get_tokens_nb(char *node)
{
	int	nb;
	int	i;

	nb = 0;
	i = 0;
	while (node[i])
	{
		if (node[i] != '\t' && node[i] != ' ')
		{
			while (node[i] != '\t' && node[i] != ' ')
				i++;
			nb++;
		}
		while (node[i] == '\t' || node[i] == ' ')
			i++;
	}
	return (nb);
}

char	*get_file_name(t_node *node, char *raw_node, int *j)
{
	char	*name;

	name = NULL;
	(void)j;
	// while (raw_node && raw_node[*j])
	// {

	// }
	node->cmd[0] = ft_strdup(raw_node);
	return (name);
}

void	add_file(t_node *node, char *raw_node, int redir, int *j)
{
	static int	pos_infiles;
	static int	pos_outfiles;

	pos_infiles = 0;
	pos_outfiles = 0;
	if (redir == 1)
	{
		node->infiles = malloc(100);
		node->infiles[pos_infiles].redir = redir;
		// node->infiles[pos_infiles].name = get_file_name(node, raw_node, j);
		node->infiles[pos_infiles].pos = *j;
		pos_infiles++;
	}
	else if (redir == 2 || redir == 3)
	{
		node->outfiles[pos_outfiles].redir = redir;
		// node->outfiles[pos_outfiles].name = get_file_name(node, raw_node, j);
		node->outfiles[pos_outfiles].pos = *j;
		pos_outfiles++;
	}
	node->cmd[0] = get_file_name(node, raw_node, j);
	if (!node->cmd[0])
		return ;
}

void	add_files_redir(t_node *nodes, t_parsing *ps)
{
	int	i;
	// t_token	*token;
	// t_shell	g_shell;
	// int	nb_token;
	int j;

	i = -1;
	while (ps->nodes && ps->nodes[++i])
	{
		j = -1;
		while (ps->nodes[i][++j])
		{
			// if (ps->nodes[i][j] == '<')
			// {
			// 	if (ps->nodes[i][j + 1] == '<')
			// 	{
			// 		// here doc
			// 		j++;
			// 	}
			// 	else if (ps->nodes[i][j + 1])
			// 	{
			// 		// on ajoute comme infile la prochaine str (skippe les espaces et go jusque espace / fin)
			// 		add_file(&nodes[i], ps->nodes[i], 1, &j);
			// 	}
			// }
			// else if (ps->nodes[i][j] == '>')
			// {
			// 	if (ps->nodes[i][j + 1] == '>')
			// 	{
			// 		// on ajoute comme outfile + APPEND
			// 		add_file(&nodes[i], ps->nodes[i], 3, &j);
			// 		j++;
			// 	}
			// 	else if (ps->nodes[i][j + 1])
			// 	{
			// 		add_file(&nodes[i], ps->nodes[i], 2, &j);
			// 		// on ajoute comme outfile
			// 	}
			// }
			add_file(&nodes[i], ps->nodes[i], 2, &j);
		}
	}	
}

t_node	*parse(t_node *nodes, t_parsing *parstruct)
{
	int i;

	if (!check_quotes_for_pipe_split(parstruct))
		return (NULL);
	parstruct->nodes = ft_split(parstruct->prompt, '|');
	if (!parstruct->nodes)
		// return (ret_err(NULL, "Parsing error : couldn't malloc to create nodes"));
		return (NULL);
	parstruct->pipe_nb = arr_len(parstruct->nodes) - 1;
	nodes = malloc(sizeof(t_node) * (parstruct->pipe_nb + 1));
	if (!nodes)
		// return (ret_err(NULL, "Parsing error : couldn't malloc to create nodes"));
		return (NULL);
	// temporaire juste pour passer la commande
	i = -1;
	while(parstruct->nodes[++i])
	{
		nodes[i].cmd = malloc(sizeof(char *) * 2);
		nodes[i].cmd[0] = ft_strdup(parstruct->nodes[i]);
		nodes[i].cmd[1] = NULL;
	}
	
	/*partie experimentale pour test les infiles dans exec*/
	nodes[0].infiles = malloc(sizeof(t_token) * 4);
	nodes[0].infiles[0].redir = 1;
	nodes[0].infiles[0].pos = 0;
	nodes[0].infiles[0].name = ft_strdup("pouette");

	nodes[0].infiles[1].redir = 1;
	nodes[0].infiles[1].pos = 0;
	nodes[0].infiles[1].name = ft_strdup("infile2");
	
	nodes[0].infiles[2].redir = 1;
	nodes[0].infiles[2].pos = 0;
	nodes[0].infiles[2].name = ft_strdup("infile3");
	
	nodes[0].infiles[3].redir = 0;
	nodes[0].infiles[3].pos = 0;
	nodes[0].infiles[3].name = NULL;


	nodes[0].outfiles = malloc(sizeof(t_token) * 3);
	nodes[0].outfiles[0].redir = 2;
	nodes[0].outfiles[0].pos = 0;
	nodes[0].outfiles[0].name = ft_strdup("out1");

	nodes[0].outfiles[1].redir = 2;
	nodes[0].outfiles[1].pos = 0;
	nodes[0].outfiles[1].name = ft_strdup("out2");
	
	nodes[0].outfiles[2].redir = 0;
	nodes[0].outfiles[2].pos = 0;
	nodes[0].outfiles[2].name = NULL;
	/* fin de la partie experimentale, deso */

	return (nodes);
	// add_files_redir(nodes, parstruct);
}
