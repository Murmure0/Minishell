#include "../../includes/minishell.h"

int	get_files_nb(char *node, char chevron)
{
	int	i;
	int nb;

	i = -1;
	nb = 0;
	while (node && node[++i])
	{
		if (node[i] == chevron)
		{
			while (node[i] && node[i] == chevron)
				i++;
			nb++;
		}
	}
	return (nb);
}

char	*get_file_name(t_parsing *ps, t_node *nodes, int redir)
{
	int		pos_start;

	ps->j++;
	skip_spaces(ps);
	pos_start = ps->j;
	while (ps->nodes[ps->i] && ps->nodes[ps->i][ps->j])
	{
		if (is_space(ps->nodes[ps->i][ps->j]) || is_chevron(ps->nodes[ps->i][ps->j]))
			break ;
		ps->j++;
	}
	if (redir == 1 && nodes->invalid_infile)
		return (NULL);
	printf("|%c| pos : %d\n", ps->nodes[ps->i][ps->j], ps->j);
	return (str_slice(ps->nodes[ps->i], pos_start, ps->j));
}

int	add_file(t_node *nodes, t_parsing *ps, int redir)
{
	int	try_open;

	try_open = 0;
	if (redir == 1 && !nodes->invalid_infile)
	{
		nodes[ps->i].infiles = get_file_name(ps, nodes, 1);
		if (access(nodes[ps->i].infiles, F_OK) != 0)
		{
			nodes->invalid_infile = 1;
		}
	}
	else if (redir == 1 && nodes->invalid_infile)
	{
		get_file_name(ps, nodes, 1);
	}
	else if (redir == 2 || redir == 3)
	{
		if (nodes[ps->i].outfiles)
			free(nodes[ps->i].outfiles);
		nodes[ps->i].outfiles = get_file_name(ps, nodes, 2);
		nodes[ps->i].append = redir;
		if (redir == 2)
		{
			try_open = open(nodes[ps->i].outfiles, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		}
		else
			try_open = open(nodes[ps->i].outfiles, O_WRONLY | O_APPEND | O_CREAT, 0644);
		if (try_open < 0)
			return (0); // perror : couldnt create file
		close(try_open);
	}
	return (1);
}