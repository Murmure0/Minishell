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

void	check_after_chevron()
{

}

//void	tokenize(t_node *first_node, t_parsing *parstruct, char *raw_node)
t_node	*tokenize(t_parsing *parstruct, char *raw_node)
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
	/*
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
	*/
	//node = create_lst_node(NULL, NULL, &tokens[0], parstruct->pipe_nb);
	first_node = new_node(NULL, NULL, tokens); //pour le premier node
	// printf("%s\n", first_node->cmd[0]);
	// printf("%s\n", first_node->cmd[1]);
	// printf("%s\n", first_node->cmd[2]);
	// printf("%s\n", first_node->cmd[3]);
	//pour les nodes suivants on utilisera :
	//node_add_back(first_node, lst_infile, lst_outfile, cmd);
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
	return(first_node);
}

//void	parse(t_parsing *parstruct)
t_node	*parse(t_parsing *parstruct)
{
	t_node *first_node;

	first_node = NULL;
	check_quotes_for_pipe_split(parstruct);
	parstruct->nodes = ft_split(parstruct->prompt, '|');
	parstruct->pipe_nb = arr_len(parstruct->nodes) - 1; //obsolete
	if (!parstruct->nodes)
		ft_exit();
	while (parstruct->nodes && *parstruct->nodes)
	{
		//tokenize(&first_node, parstruct, *parstruct->nodes); 
		first_node = tokenize(parstruct, *parstruct->nodes);
		// printf("%s\n", *parstruct->nodes);
		parstruct->nodes++;
	}
	return (first_node);
}	
