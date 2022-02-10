#include "../../includes/minishell.h"

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

int	process_parse(t_node **nodes, t_parsing *ps, t_shell *sh)
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
			add_file(*nodes, ps, 1, sh);
		}
		else
			return (ret_err(0, NO_FILE));
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
			if (!add_file(*nodes, ps, 3, sh))
				return (0);
		}
		else if (ps->nodes[ps->i][ps->j + 1])
		{
			if (!add_file(*nodes, ps, 2, sh))
				return (0);
			printf("add outfile name\n");
		}
		else
			return (ret_err(0, NO_FILE));
	}
	else
	{
		add_command(nodes, ps);
	}
	return (1);
}

t_node	*parse(t_parsing *ps, t_shell *sh)
{
	t_node *nodes;

	if (!init_global_struct(ps, sh))
		return (NULL);
	nodes = malloc(sizeof(t_node) * (ps->pipe_nb + 1));
	if (!nodes)
		ft_exit(sh, ps, NULL, "Fail to malloc nodes\n");
	while(ps->nodes[ps->i])
	{
		init_local_struct(&nodes, &ps, sh);
		while (ps->nodes[ps->i][ps->j])
		{
			skip_spaces(ps);
			if (!process_parse(&nodes, ps, sh))
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
