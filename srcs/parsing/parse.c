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
	while (ps->nodes[ps->i][ps->j] && (ps->nodes[ps->i][ps->j] == '\t' || ps->nodes[ps->i][ps->j] == ' '))
		ps->j++;
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
			if (!process_parse(nodes, ps))
				return (NULL);
			if (ps->nodes[ps->i][ps->j] && ps->nodes[ps->i][ps->j + 1])
				ps->j++;
		}
		ps->i++;
	}

	/*partie experimentale pour test les infiles dans exec*/
	
	// nodes[0].infiles = malloc(sizeof(t_token) * 5);

	// nodes[0].infiles[0].redir = 1;
	// nodes[0].infiles[0].pos = 0;
	// nodes[0].infiles[0].name = ft_strdup("pouette");

	// nodes[0].infiles[1].redir = 1;
	// nodes[0].infiles[1].pos = 0;
	// nodes[0].infiles[1].name = ft_strdup("infile2");
	
	// nodes[0].infiles[2].redir = 1;
	// nodes[0].infiles[2].pos = 0;
	// nodes[0].infiles[2].name = ft_strdup("infile3");
	
	// nodes[0].infiles[3].redir = 0;
	// nodes[0].infiles[3].pos = 0;
	// nodes[0].infiles[3].name = NULL;


	// nodes[0].outfiles = malloc(sizeof(t_token) * 3);
	// nodes[0].outfiles[0].redir = 2;
	// nodes[0].outfiles[0].pos = 0;
	// nodes[0].outfiles[0].name = ft_strdup("out1");

	// nodes[0].outfiles[1].redir = 3;
	// nodes[0].outfiles[1].pos = 0;
	// nodes[0].outfiles[1].name = ft_strdup("out2");
	
	// nodes[0].outfiles[2].redir = 0;
	// nodes[0].outfiles[2].pos = 0;
	// nodes[0].outfiles[2].name = NULL;
	/* fin de la partie experimentale, deso */

	return (nodes);
}
