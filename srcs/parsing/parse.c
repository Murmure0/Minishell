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

/*void	tokenize(t_node *node, t_parsing *parstruct, char *raw_node)
{
	int	i;
	char	**tokens;
	// t_token	*token;
	t_node *first_node;

	// faire un split special avec non printable chars ? (ascii entre 9 et 13)
	tokens = ft_split(raw_node, ' ');
	if (!tokens)
		ft_exit();
	i = -1;
	
	if (tokens[0][0] == '<')
	{
		parstruct->chevron = '<';
		if (tokens[0][1] == parstruct->chevron)
		{
			// checker si il a autre chose dans la string
			if (tokens[0][2] && (tokens[0][2] != '<' && tokens[0][2] != '>'))
			{
				token = new_token(redir_l, tokens[0]); // tokens[0] = copie sans les >>
			}
			token = new_token(redir_l, tokens[1]); // le prochain token sera le heredoc
			// lancer la fonction heredoc
		}
		else if (tokens[0][1])
		{
			// si on a autre chose quun char alphanumerique apres => err
			// if (!ft_isalnum(tokens[0][2]))
			//		ft_exit();
			// copier tokens[0] (qui contient infile) sans le < 
			// i++;
		}
	}
	else if (tokens[0][0] == '>')
	{
		parstruct->chevron = '>';
		if (tokens[0][1] == parstruct->chevron)
		{
			// si on a autre chose quun char alphanumerique apres => err
			if (tokens[0][2])
			{
				//  if (!ft_isalnum(tokens[0][2]))
				//		ft_exit();
				// copier tokens[0] (qui contient infile) sans le < 
				token = new_token(redir_r_d, tokens[0]); // tokens[0] = copie sans les >>
			}
			else
			{
				token = new_token(redir_r_d, tokens[1]); // le prochain token sera le file
			}
		}
		else if (tokens[0][1] && ft_isalnum(tokens[0][1]))
		{
			// si on a un chevron, on check
		}
	}
	else
	{
		token = new_token(no_redir, tokens[0]);
	}

	node = create_lst_node(NULL, NULL, &tokens[0], parstruct->pipe_nb);
	// printf("%s\n", node->cmd[0]);
	while (tokens[++i])
	{
		// if (tokens[i] == '<' || tokens[i] == '>')
		// 	check_after_chevron();

		// commencer par les tokens
		// si tokens[0] est un chevron sans rien qui suit, tokens[1] sera un file
		// si tokens[0][0] est un chevron, verifier ce quil y a apres 
		// 		si cest un autre chevron, 
		//			si il y a un autre chevron ou un char special => err
		//		sinon on aura un file apres
		// une fois les tokens crees, on peut creer les nodes
		// printf("%s\n", tokens[i]);
	}
	//(void)node;
	(void)parstruct;
}*/

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
	// while (raw_node && raw_node[*j])
	// {

	// }
	node->cmd = ft_strdup(raw_node);
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
		// printf("here\n");
		// node->infiles[pos_infiles].name = get_file_name(node, raw_node, j);
		node->infiles[pos_infiles].pos = *j;
		// printf("%d\n", node->infiles[pos_infiles].pos);
		pos_infiles++;
	}
	else if (redir == 2 || redir == 3)
	{
		node->outfiles[pos_outfiles].redir = redir;
		// node->outfiles[pos_outfiles].name = get_file_name(node, raw_node, j);
		node->outfiles[pos_outfiles].pos = *j;
		pos_outfiles++;
	}
	node->cmd = get_file_name(node, raw_node, j);
}

void	add_files_redir(t_node *nodes, t_parsing *ps)
{
	int	i;
	t_token	*token;
	t_shell	g_shell;
	int	nb_token;
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
	t_shell	g_shell;
	int i;

	check_quotes_for_pipe_split(parstruct);
	parstruct->nodes = ft_split(parstruct->prompt, '|');
	parstruct->pipe_nb = arr_len(parstruct->nodes) - 1;
	if (!parstruct->nodes)
		ft_exit(g_shell);
	nodes = malloc(sizeof(t_node) * (parstruct->pipe_nb + 1));
	if (!nodes)
		ft_exit(g_shell);
	i = -1;
	while(parstruct->nodes[++i])
	{
		nodes[i].cmd = malloc(sizeof(char *) * 2);
		nodes[i].cmd[0] = ft_strdup(parstruct->nodes[i]);
		nodes[i].cmd[1] = NULL;
	}
	return (nodes);
	// nodes[0].infiles[0].name = ft_strdup("infile");
	// add_files_redir(nodes, parstruct);
}
