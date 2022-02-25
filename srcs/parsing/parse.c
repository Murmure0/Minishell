/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmasse <vmasse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 17:00:41 by vmasse            #+#    #+#             */
/*   Updated: 2022/02/25 09:48:39 by vmasse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// extern int g_exit_st;

int	parse_case_infile(t_node *nodes, t_parsing *ps, t_shell *sh)
{
	if (!check_space_between_redirs(ps))
	{
		ps->stop_err = 1;
		return (0);
	}
	if (ps->nodes[ps->i][ps->j + 1] && ps->nodes[ps->i][ps->j + 1] == '<')
	{
		if(!nodes[ps->i].invalid_infile)
			nodes[ps->i].in_id = 1;
		ps->j++;
		if (add_heredoc_file(nodes, ps))
		{
			ps->stop_err = 1;
			return (0);
		}
		// if (g_exit_st == 130)
		// {
			write(1, "pouet\n", 6);
		// 	return (ret_err(0, NO_FILE));
		// }
	}
	else if (ps->nodes[ps->i][ps->j + 1])
	{
		nodes[ps->i].in_id = 2;
		add_file(nodes, ps, 1, sh);
	}
	else
		return (ret_err(0, NO_FILE)); //tester le retour 0, maybe segfault
	return (1);
}

int	parse_case_outfile(t_node *nodes, t_parsing *ps, t_shell *sh)
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
		if (!add_file(nodes, ps, 3, sh))
			return (0);
	}
	else if (ps->nodes[ps->i][ps->j + 1])
	{
		if (!add_file(nodes, ps, 2, sh))
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
		if (!parse_case_infile(*nodes, ps, sh))
			return (0);
	}
	else if (ps->nodes[ps->i][ps->j] == '>')
	{
		if (!parse_case_outfile(*nodes, ps, sh))
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
		ft_exit(sh, ps, NULL, "Fail to malloc nodes in parse\n");
	while (ps->nodes[ps->i])
	{
		init_local_struct(&nodes, &ps, sh);
		while (ps->nodes[ps->i][ps->j])
		{
			if (!process_parse(&nodes, ps, sh))
				return (NULL);
			if (ps->nodes[ps->i][ps->j] && ps->nodes[ps->i][ps->j + 1]
				&& !is_chevron(ps->nodes[ps->i][ps->j]))
					ps->j++;
			else if (is_chevron(ps->nodes[ps->i][ps->j]))
				continue ;
			else
				break ;
		}
		ps->i++;
	}
	// expand_dollar_value_cmd(nodes, ps , sh);
	// remove_quotes_cmd(nodes, ps);
	return (nodes);
}

// "'$a $b'"

// minishell$ echo "$POP + $PIP"
// CMD : echo
// found d quote at 0
// CMD INSIDE : "2
// CMD : 2
// CMD : +
// CMD INSIDE : 3"
// ==146834== Invalid read of size 1
// ==146834==    at 0x403620: get_next_quote (parse_quotes.c:71)
// ==146834==    by 0x40397D: remove_quotes_cmd (parse_quotes.c:138)
// ==146834==    by 0x40303E: parse (parse.c:122)
// ==146834==    by 0x4014BF: main (main.c:93)
// ==146834==  Address 0x4b50842 is 0 bytes after a block of size 2 alloc'd
// ==146834==    at 0x484486F: malloc (vg_replace_malloc.c:381)
// ==146834==    by 0x40842E: ft_strjoin (in /home/vmasse/Code/Minishell/minishell)
// ==146834==    by 0x403697: remove_quote (parse_quotes.c:92)
// ==146834==    by 0x403920: remove_quotes_cmd (parse_quotes.c:136)
// ==146834==    by 0x40303E: parse (parse.c:122)
// ==146834==    by 0x4014BF: main (main.c:93)
// ==146834== 
// CMD : 3
// 2 + 3
