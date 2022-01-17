#include "../../includes/minishell.h"

void	tokenize(t_node *node, t_parsing *parstruct, char *raw_node)
{
	int	i;
	char	**tokens;

	// faire un split special avec non printable chars ? (ascii entre 9 et 13)
	tokens = ft_split(raw_node, ' ');
	if (!tokens)
		ft_exit();
	i = -1;
	while (tokens[++i])
	{

		// node = new_node(NULL, NULL, node);
		printf("%s\n", tokens[i]);
	}
	(void)node;
	(void)parstruct;
}

void	parse(t_parsing *parstruct)
{
	t_node	node;

	check_quotes_for_pipe_split(parstruct);
	parstruct->nodes = ft_split(parstruct->prompt, '|');
	if (!parstruct->nodes)
		ft_exit();
	while (parstruct->nodes && *parstruct->nodes)
	{
		tokenize(&node, parstruct, *parstruct->nodes);
		// printf("%s\n", *parstruct->nodes);
		parstruct->nodes++;
	}
<<<<<<< Updated upstream
}	
=======
}
	
>>>>>>> Stashed changes
