/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maelle <maelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 17:00:41 by vmasse            #+#    #+#             */
/*   Updated: 2022/03/14 16:24:18 by maelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_exit_st;

int	parse_case_infile(t_node *nodes, t_parsing *ps, t_shell *sh)
{
	if (!check_space_between_redirs(ps))
	{
		ps->stop_err = 1;
		return (0);
	}
	if (ps->nodes[ps->i][ps->j] == '<')
	{
		if (!parse_case_hd(nodes, ps))
			return (g_exit_st);
	}
	else if (ps->nodes[ps->i][ps->j] == '>')
		return (ret_err(0, NO_FILE));
	else if (ps->nodes[ps->i][ps->j] && ps->nodes[ps->i][ps->j + 1])
	{
		nodes[ps->i].in_id = 2;
		add_file(nodes, ps, 1, sh);
	}
	else
		return (ret_err(0, NO_FILE));
	return (1);
}

int	parse_case_outfile(t_node *nodes, t_parsing *ps, t_shell *sh)
{
	if (!check_space_between_redirs(ps))
	{
		ps->stop_err = 1;
		return (0);
	}
	if (ps->nodes[ps->i][ps->j] == '>')
	{
		ps->j++;
		if (!add_file(nodes, ps, 3, sh))
			return (0);
	}
	else if (ps->nodes[ps->i][ps->j] == '>')
		return (ret_err(0, NO_FILE));
	else if (ps->nodes[ps->i][ps->j])
	{
		if (!add_file(nodes, ps, 2, sh))
			return (0);
	}
	else
		return (ret_err(0, NO_FILE));
	return (1);
}

int	process_parse(t_node **nodes, t_parsing *ps, t_shell *sh)
{
	skip_spaces(ps);
	if (ps->nodes[ps->i][ps->j] == '<')
	{
		ps->j++;
		if (is_chevron(ps->nodes[ps->i][ps->j])
			&& is_chevron(ps->nodes[ps->i][ps->j + 1]))
			return (ret_err(0, NO_FILE));
		expand_dollar_files(*nodes, ps, sh);
		if (!parse_case_infile(*nodes, ps, sh))
			return (0);
	}
	else if (ps->nodes[ps->i][ps->j] == '>')
	{
		ps->j++;
		if (is_chevron(ps->nodes[ps->i][ps->j])
			&& is_chevron(ps->nodes[ps->i][ps->j + 1]))
			return (ret_err(0, NO_FILE));
		expand_dollar_files(*nodes, ps, sh);
		if (!parse_case_outfile(*nodes, ps, sh))
			return (0);
	}
	else
		add_command(nodes, ps, sh);
	return (1);
}

static int	inside_parse(t_node *nodes, t_parsing *ps, t_shell *sh)
{
	if (!process_parse(&nodes, ps, sh))
	{
		ps->stop_err = 1;
		free_nodestruct(nodes, ps);
		return (-1);
	}
	if (ps->nodes[ps->i][ps->j] && ps->nodes[ps->i][ps->j + 1]
		&& !is_chevron(ps->nodes[ps->i][ps->j]))
			ps->j++;
	else if (is_chevron(ps->nodes[ps->i][ps->j]))
		return (1);
	else
		return (-2);
	return (0);
}

t_node	*parse(t_parsing *ps, t_shell *sh)
{
	t_node	*nodes;
	int		ret;

	nodes = malloc(sizeof(t_node) * (ps->pipe_nb + 1));
	if (!nodes)
		ft_exit(sh, ps, NULL, "Fail to malloc nodes in parse\n");
	while (ps->nodes[ps->i])
	{
		init_local_struct(&nodes, &ps, sh);
		while (ps->nodes[ps->i][ps->j])
		{
			ret = inside_parse(nodes, ps, sh);
			if (ret == -1)
				return (NULL);
			else if (ret == 1)
				continue ;
			else if (ret == -2)
				break ;
		}
		ps->i++;
	}
	end_parse(ps, nodes, sh);
	return (nodes);
}
