#include "../../includes/minishell.h"

int	init_global_struct(t_node **nodes, t_parsing *ps)
{
	if (!check_quotes_for_pipe_split(ps))
		return (0);
	ps->nodes = ft_split(ps->prompt, '|');
	if (!ps->nodes)
		return (0);
	ps->pipe_nb = arr_len(ps->nodes) - 1;
	*nodes = malloc(sizeof(t_node) * (ps->pipe_nb + 2));
	if (!*nodes)
		return (0);
	ps->i = 0;
	return (1);
}

int	init_local_struct(t_node *nodes, t_parsing *ps)
{
	ps->pos_infiles = 0;
	ps->pos_outfiles = 0;
	ps->pos_cmd = 0;
	nodes[ps->i].infiles = malloc(sizeof(t_token) * get_files_nb(ps->nodes[ps->i], '<'));
	if (!nodes[ps->i].infiles)
		return (0);
	nodes[ps->i].outfiles = malloc(sizeof(t_token) * get_files_nb(ps->nodes[ps->i], '>'));
	if (!nodes[ps->i].outfiles)
		return (0);
	ps->j = 0;
	return (1);
}

int	process_parse(t_node *nodes, t_parsing *ps)
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
			return (0); // erreur -> no infile
	}
	else if (ps->nodes[ps->i][ps->j] == '>')
	{
		if (ps->nodes[ps->i][ps->j + 1] && ps->nodes[ps->i][ps->j + 1] == '>')
		{
			printf("add outfile + append\n");
			ps->j++;
			add_file(nodes, ps, 3);
		}
		else if (ps->nodes[ps->i][ps->j + 1])
		{
			add_file(nodes, ps, 2);
			printf("add outfile name\n");
		}
		else
			return (0); // erreur -> no outfile
	}
	else
	{
		add_command(&nodes, ps);
	}
	return (1);
}

t_node	*parse(t_node *nodes, t_parsing *ps)
{
	if (!init_global_struct(&nodes, ps))
		return (NULL);
	while(ps->nodes[ps->i])
	{
		if (!init_local_struct(nodes, ps))
			return (NULL);
		while (ps->nodes[ps->i][ps->j])
		{
			skip_spaces(ps);
			if (!process_parse(nodes, ps))
				return (NULL);
			if (ps->nodes[ps->i][ps->j] && ps->nodes[ps->i][ps->j + 1])
				ps->j++;
		}
		ps->i++;
	}
	return (nodes);
}
