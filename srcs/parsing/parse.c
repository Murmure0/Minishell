#include "../../includes/minishell.h"

int	init_global_struct(t_parsing *ps)
{
	if (!check_quotes_for_pipe_split(ps))
		return (0);
	ps->nodes = ft_split(ps->prompt, '|');
	if (!ps->nodes)
		return (0);
	ps->pipe_nb = arr_len(ps->nodes) - 1;
	ps->stop_err = 0;
	ps->i = 0;
	return (1);
}

int	init_local_struct(t_node **nodes, t_parsing **ps)
{
	(*ps)->pos_cmd = 0;
	(*ps)->j = 0;
	(*ps)->nodes[(*ps)->i] = ft_strtrim((*ps)->nodes[(*ps)->i], " ");
	if (!(*ps)->nodes[(*ps)->i])
		return (0);
	(*ps)->nodes[(*ps)->i] = ft_strtrim((*ps)->nodes[(*ps)->i], "\t");
	if (!(*ps)->nodes[(*ps)->i])
		return (0);
	(*nodes)[(*ps)->i].infiles = 0;
	(*nodes)[(*ps)->i].outfiles = 0;
	(*nodes)[(*ps)->i].append = 0;
	(*nodes)[(*ps)->i].invalid_infile = 0;
	(*ps)->cmd_nb = get_cmds_nb((*ps)->nodes[(*ps)->i]);
	(*nodes)[(*ps)->i].cmd = malloc(sizeof(char *) * ((*ps)->cmd_nb + 1));
	if (!(*nodes)[(*ps)->i].cmd)
		return (0);
	if (!(*ps)->cmd_nb)
		(*nodes)[(*ps)->i].cmd = 0;
	return (1);
}

int	check_space_between_redirs(t_parsing *ps)
{
	int	j;

	j = ps->j;
	if (ps->nodes[ps->i][j + 1] && ps->nodes[ps->i][j + 1] && is_space(ps->nodes[ps->i][j + 1]))
	{
		j++;
		while (ps->nodes[ps->i][j] && is_space(ps->nodes[ps->i][j]))
		{
			if (ps->nodes[ps->i][j + 1])
				j++;
			else
				break ;
		}
		if (ps->nodes[ps->i][j] && is_chevron(ps->nodes[ps->i][j]))
		{
			printf("minishell: syntax error near unexpected token `%c'\n", ps->nodes[ps->i][j]);
			return (0);
		}
	}
	return (1);
}

int	process_parse(t_node **nodes, t_parsing *ps)
{
	if (ps->nodes[ps->i][ps->j] == '<')
	{
		if (!check_space_between_redirs(ps))
		{
			ps->stop_err = 1;
			return (0);
		}
		if (ps->nodes[ps->i][ps->j + 1] && ps->nodes[ps->i][ps->j + 1] == '<')
		{
			printf("add heredoc\n");
			ps->j++;
		}
		else if (ps->nodes[ps->i][ps->j + 1])
		{
			printf("add infile name\n");
			add_file(*nodes, ps, 1);
		}
		else
			return (0); // erreur -> no infile
	}
	else if (ps->nodes[ps->i][ps->j] == '>')
	{
		if (!check_space_between_redirs(ps))
		{
			ps->stop_err = 1;
			return (0);
		}
		if (ps->nodes[ps->i][ps->j + 1] && ps->nodes[ps->i][ps->j + 1] == '>')
		{
			printf("add outfile + append\n");
			ps->j++;
			if (!add_file(*nodes, ps, 3))
				return (0);
		}
		else if (ps->nodes[ps->i][ps->j + 1])
		{
			if (!add_file(*nodes, ps, 2))
				return (0);
			printf("add outfile name\n");
		}
		else
			return (0); // erreur -> no outfile
	}
	else
	{
		add_command(nodes, ps);
	}
	return (1);
}

t_node	*parse(t_parsing *ps)
{
	t_node *nodes;

	if (!init_global_struct(ps))
		return (NULL);
	nodes = malloc(sizeof(t_node) * (ps->pipe_nb + 1));
	if (!nodes)
		return (NULL);
	while(ps->nodes[ps->i])
	{
		if (!init_local_struct(&nodes, &ps))
			return (NULL);
		while (ps->nodes[ps->i][ps->j])
		{
			skip_spaces(ps);
			if (!process_parse(&nodes, ps))
				return (NULL);
			if (ps->nodes[ps->i][ps->j] && ps->nodes[ps->i][ps->j + 1] &&
				ps->nodes[ps->i][ps->j] != '<' && ps->nodes[ps->i][ps->j] != '>')
					ps->j++;
			else if (is_chevron(ps->nodes[ps->i][ps->j]))
				continue ;
			else
				break ;
		}
		ps->i++;
	}
	return (nodes);
}
