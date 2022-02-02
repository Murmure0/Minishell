#include "../../includes/minishell.h"

char	*get_file_name(t_parsing *ps)
{
	int		pos_start;

	pos_start = ps->j;
	while (ps->nodes[ps->i] && ps->nodes[ps->i][++(ps->j)])
	{
		while (ps->nodes[ps->i][ps->j] == '\t' || ps->nodes[ps->i][ps->j] == ' ')
			ps->j++;
		if (ps->nodes[ps->i][ps->j] == '\t' || ps->nodes[ps->i][ps->j] == ' ' || ps->nodes[ps->i][ps->j] == '<' || ps->nodes[ps->i][ps->j] == '>')
		{
			ps->j++;
			break ;
		}
	}
	return (str_slice(ps->nodes[ps->i], pos_start, ps->j));
}

void	add_file(t_node *nodes, t_parsing *ps, int redir)
{
	static int	pos_infiles;
	static int	pos_outfiles;

	pos_infiles = 0;
	pos_outfiles = 0;
	if (redir == 1)
	{
		nodes[ps->i].infiles[pos_infiles].redir = redir;
		nodes[ps->i].infiles[pos_infiles].name = get_file_name(ps);
		nodes[ps->i].infiles[pos_infiles].pos = ps->j;
		pos_infiles++;
	}
	else if (redir == 2 || redir == 3)
	{
		nodes[ps->i].outfiles[pos_outfiles].redir = redir;
		nodes[ps->i].outfiles[pos_outfiles].name = get_file_name(ps);
		nodes[ps->i].outfiles[pos_outfiles].pos = ps->j;
		pos_outfiles++;
	}
}

t_node	*parse(t_node *nodes, t_parsing *ps)
{
	if (!check_quotes_for_pipe_split(ps))
		return (NULL);
	ps->nodes = ft_split(ps->prompt, '|');
	if (!ps->nodes)
		return (NULL);
	ps->pipe_nb = arr_len(ps->nodes) - 1;
	nodes = malloc(sizeof(t_node) * (ps->pipe_nb + 1));
	if (!nodes)
		return (NULL);
	ps->i = -1;
	while(ps->nodes[++(ps->i)])
	{
		nodes[ps->i].infiles = malloc(sizeof(t_token *) * get_files_nb(ps->nodes[ps->i], '<'));
		if (!nodes[ps->i].infiles)
			return (NULL);
		nodes[ps->i].outfiles = malloc(sizeof(t_token *) * get_files_nb(ps->nodes[ps->i], '>'));
		if (!nodes[ps->i].outfiles)
			return (NULL);
		ps->j = -1;
		while (ps->nodes[ps->i][++(ps->j)])
		{
			if (ps->nodes[ps->i][ps->j] == '<')
			{
				if (ps->nodes[ps->i][ps->j + 1] && ps->nodes[ps->i][ps->j + 1] == '<')
				{
					printf("add heredoc\n");
					ps->j++;
				}
				else if (ps->nodes[ps->i][ps->j + 1])
				{
					printf("add infile name\n");
					add_file(nodes, ps, 1);
				}
				else
					return (NULL); // erreur -> no infile
			}
			else if (ps->nodes[ps->i][ps->j] == '>')
			{
				if (ps->nodes[ps->i][ps->j + 1] && ps->nodes[ps->i][ps->j + 1] == '>')
				{
					printf("add outfile + append\n");
					add_file(nodes, ps, 3);
					ps->j++;
				}
				else if (ps->nodes[ps->i][ps->j + 1])
				{
					add_file(nodes, ps, 2);
					printf("add outfile name\n");
				}
				else
					return (NULL); // erreur -> no outfile
			}
		}
	}
	return (nodes);
}
