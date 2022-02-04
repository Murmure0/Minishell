#include "../../includes/minishell.h"

char	*get_file_name(t_parsing *ps)
{
	int		pos_start;

	ps->j++;
	while (ps->nodes[ps->i] && ps->nodes[ps->i][ps->j] && (ps->nodes[ps->i][ps->j] == '\t' || ps->nodes[ps->i][ps->j] == ' '))
		ps->j++;
	pos_start = ps->j;
	while (ps->nodes[ps->i] && ps->nodes[ps->i][ps->j])
	{
		if (ps->nodes[ps->i][ps->j] == '\t' || ps->nodes[ps->i][ps->j] == ' ' || ps->nodes[ps->i][ps->j] == '<' || ps->nodes[ps->i][ps->j] == '>')
			break ;
		ps->j++;
	}
	return (str_slice(ps->nodes[ps->i], pos_start, ps->j));
}

void	add_file(t_node *nodes, t_parsing *ps, int redir)
{
	if (redir == 1)
	{
		nodes[ps->i].infiles[ps->pos_infiles].redir = redir;
		nodes[ps->i].infiles[ps->pos_infiles].name = get_file_name(ps);
		nodes[ps->i].infiles[ps->pos_infiles].pos = ps->j;
		ps->pos_infiles++;
	}
	else if (redir == 2 || redir == 3)
	{
		nodes[ps->i].outfiles[ps->pos_outfiles].redir = redir;
		nodes[ps->i].outfiles[ps->pos_outfiles].name = get_file_name(ps);
		nodes[ps->i].outfiles[ps->pos_outfiles].pos = ps->j;
		ps->pos_outfiles++;
	}
	// add_command(nodes, ps);
}