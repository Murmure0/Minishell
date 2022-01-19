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
	(void)node;
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

void	create_nodes(t_node *nodes, char **raw_nodes)
{
	int	i;
	t_token	*token;
	int	nb_token;

	while (raw_nodes && *raw_nodes)
	{
		nb_token = get_tokens_nb(*raw_nodes);
		token = malloc(sizeof(t_token) * nb_token);
		if (!token)
			ft_exit();
		i = -1;
		while (*raw_nodes[++i])
		{
			if (*raw_nodes[i] != '\t' && *raw_nodes[i] != ' ')
			{
				token[i].pos = i;
				while (*raw_nodes[i] != '\t' && *raw_nodes[i] != ' ')
					i++;
				token[i].name = ft_slice(*raw_nodes, token[i].pos, i);
				if (!token[i].name)
					ft_exit();
			}
			while (*raw_nodes[i] == '\t' || *raw_nodes[i] == ' ')
				i++;
		}
		raw_nodes++;
		// ajouter dans le node infiles et outfiles
		(void)nodes;
	}
}

void	parse(t_parsing *parstruct)
{
	t_node	*nodes;

	check_quotes_for_pipe_split(parstruct);
	parstruct->nodes = ft_split(parstruct->prompt, '|');
	parstruct->pipe_nb = arr_len(parstruct->nodes) - 1;
	if (!parstruct->nodes)
		ft_exit();
	nodes = malloc(sizeof(t_node) * parstruct->pipe_nb);
	if (!nodes)
		ft_exit();
	// create_nodes(nodes, parstruct->nodes);
}