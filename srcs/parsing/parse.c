#include "../../includes/minishell.h"

char	*get_file_name(char *raw_node, int *j)
{
	char	*name;
	int		pos_start;

	name = NULL;
	pos_start = *j;
	while (raw_node && raw_node[++(*j)])
	{
		while (raw_node[*j] == '\t' || raw_node[*j] == ' ')
			(*j)++;
		if (raw_node[*j] == '\t' || raw_node[*j] == ' ' || raw_node[*j] == '<' || raw_node[*j] == '>')
		{
			(*j)++;
			break ;
		}
	}
	return (str_slice(raw_node, pos_start, *j));
}

void	add_file(t_node *node, char *raw_node, int redir, int *j)
{
	static int	pos_infiles;
	static int	pos_outfiles;

	pos_infiles = 0;
	pos_outfiles = 0;
	if (redir == 1)
	{
		// node->infiles = malloc(100);
		node->infiles[pos_infiles].redir = redir;
		// node->infiles[pos_infiles].name = get_file_name(node, raw_node, j);
		node->infiles[pos_infiles].pos = *j;
		pos_infiles++;
	}
	else if (redir == 2 || redir == 3)
	{
		// node->outfiles = malloc(100);
		node->outfiles[pos_outfiles].redir = redir;
		// node->outfiles[pos_outfiles].name = get_file_name(node, raw_node, j);
		node->outfiles[pos_outfiles].pos = *j;
		pos_outfiles++;
	}
	node->cmd[0] = get_file_name(raw_node, j);
	printf("%s\n", node->cmd[0]);
	if (!node->cmd[0])
		return ;
}

void	add_files_redir(t_node *nodes, t_parsing *ps)
{
	int	i;
	// t_token	*token;
	int j;

	i = -1;
	while (ps->nodes && ps->nodes[++i])
	{
		j = -1;
		nodes[i].infiles = malloc(sizeof(t_token) * get_files_nb(ps->nodes[i], '<'));
		if (!nodes[i].infiles)
			return ;
		nodes[i].outfiles = malloc(sizeof(t_token) * get_files_nb(ps->nodes[i], '>'));
		if (!nodes[i].outfiles)
			return ;
		while (ps->nodes[i][++j])
		{
			if (ps->nodes[i][j] == '<')
			{
				if (ps->nodes[i][j + 1] == '<')
				{
					// here doc
					j++;
				}
				else if (ps->nodes[i][j + 1])
				{
					// on ajoute comme infile la prochaine str (skippe les espaces et go jusque espace / fin)
					add_file(&nodes[i], ps->nodes[i], 1, &j);
				}
			}
			else if (ps->nodes[i][j] == '>')
			{
				if (ps->nodes[i][j + 1] == '>')
				{
					// on ajoute comme outfile + APPEND
					add_file(&nodes[i], ps->nodes[i], 3, &j);
					j++;
				}
				else if (ps->nodes[i][j + 1])
				{
					add_file(&nodes[i], ps->nodes[i], 2, &j);
					// on ajoute comme outfile
				}
			}
			// pourquoi ??
			add_file(&nodes[i], ps->nodes[i], 2, &j);
		}
	}	
}

t_node	*parse(t_node *nodes, t_parsing *parstruct)
{
	// int i;

	if (!check_quotes_for_pipe_split(parstruct))
		return (NULL);
	parstruct->nodes = ft_split(parstruct->prompt, '|');
	if (!parstruct->nodes)
		return (NULL);
		// return (ret_err(NULL, "Parsing error : couldn't malloc to create nodes"));
	parstruct->pipe_nb = arr_len(parstruct->nodes) - 1;
	nodes = malloc(sizeof(t_node) * (parstruct->pipe_nb + 1));
	if (!nodes)
		return (NULL);
		// return (ret_err(NULL, "Parsing error : couldn't malloc to create nodes"));

	// temporaire juste pour passer la commande
	// i = -1;
	// while(parstruct->nodes[++i])
	// {
	// 	// nodes[i].cmd = malloc(sizeof(char *) * 2);
	// 	// nodes[i].cmd[0] = ft_strdup(parstruct->nodes[i]);
	// 	// nodes[i].cmd[1] = NULL;
	// }

	// nodes[0].infiles[0].name = ft_strdup("infile");
	// add_files_redir(nodes, parstruct);
	return (nodes);
}
