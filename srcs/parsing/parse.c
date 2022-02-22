/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maelle <maelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 17:00:41 by vmasse            #+#    #+#             */
/*   Updated: 2022/02/22 09:33:17 by maelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	parse_case_infile(t_node **nodes, t_parsing *ps, t_shell *sh)
{
	if (!check_space_between_redirs(ps))
	{
		ps->stop_err = 1;
		return (0);
	}
	if (ps->nodes[ps->i][ps->j + 1] && ps->nodes[ps->i][ps->j + 1] == '<')
	{
		if(!nodes[ps->i]->invalid_infile) //
			nodes[ps->i]->in_id = 1; //
		printf("add heredoc\n");
		ps->j++;
		add_heredoc_file(*nodes, ps); //

	}
	else if (ps->nodes[ps->i][ps->j + 1])
	{
		nodes[ps->i]->in_id = 2; //
		printf("add infile name\n");
		add_file(*nodes, ps, 1, sh);
	}
	else
		return (ret_err(0, NO_FILE));
	printf("VALEUR DE inID : %d\n", nodes[ps->i]->in_id);
	return (1);
}

int	parse_case_outfile(t_node **nodes, t_parsing *ps, t_shell *sh)
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
	return (1);
}

int	process_parse(t_node **nodes, t_parsing *ps, t_shell *sh)
{
	skip_spaces(ps);
	if (ps->nodes[ps->i][ps->j] == '<')
	{
		if (!parse_case_infile(nodes, ps, sh))
			return (0);
	}
	else if (ps->nodes[ps->i][ps->j] == '>')
	{
		if (!parse_case_outfile(nodes, ps, sh))
			return (0);
	}
	else
	{
		add_command(nodes, ps, sh);
	}
	return (1);
}

t_node	*parse(t_parsing *ps, t_shell *sh)
{
	t_node	*nodes;

	if (!init_global_struct(ps, sh))
		return (NULL);
	nodes = malloc(sizeof(t_node) * (ps->pipe_nb + 1));
	if (!nodes)
		ft_exit(sh, ps, NULL, "Fail to malloc nodes\n");
	while (ps->nodes[ps->i])
	{
		init_local_struct(&nodes, &ps, sh);
		while (ps->nodes[ps->i][ps->j])
		{
			if (!process_parse(&nodes, ps, sh))
				return (NULL);
			if (ps->nodes[ps->i][ps->j] && ps->nodes[ps->i][ps->j + 1] &&
				!is_chevron(ps->nodes[ps->i][ps->j]))
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
