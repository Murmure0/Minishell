/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmasse <vmasse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 14:05:56 by vmasse            #+#    #+#             */
/*   Updated: 2022/03/14 15:05:38 by vmasse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_files_nb(char *node, char chevron)
{
	int	i;
	int	nb;

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
	int		count_s;
	int		count_d;

	skip_spaces(ps);
	pos_start = ps->j;
	count_d = 0;
	count_s = 0;
	while (ps->nodes[ps->i] && ps->nodes[ps->i][ps->j])
	{
		if (ps->nodes[ps->i][ps->j] == '"')
			count_d++;
		if (ps->nodes[ps->i][ps->j] == '\'')
			count_s++;
		set_quotes_for_getfilename(ps, ps->j, &count_s, &count_d);
		if ((is_space(ps->nodes[ps->i][ps->j])
			|| is_chevron(ps->nodes[ps->i][ps->j]))
			&& !ps->is_d_quote && !ps->is_s_quote)
			break ;
		ps->j++;
	}
	if (redir == 1 && nodes[ps->i].invalid_infile)
		return (NULL);
	return (str_slice(ps->nodes[ps->i], pos_start, ps->j));
}

void	add_infile(t_node *nodes, t_parsing *ps, t_shell *sh)
{
	if (nodes[ps->i].infiles)
		free(nodes[ps->i].infiles);
	nodes[ps->i].infiles = get_file_name(ps, nodes, 1);
	if (!nodes[ps->i].infiles)
		ft_exit(sh, ps, nodes, "Fail to malloc infiles in add_file\n");
	nodes[ps->i].infiles = remove_quotes_files(ps, nodes[ps->i].infiles);
	if (!nodes[ps->i].infiles)
		ft_exit(sh, ps, nodes, "Fail to malloc infiles in add_file\n");
	if (access(nodes[ps->i].infiles, F_OK) != 0)
		nodes[ps->i].invalid_infile = 1;
}

int	add_outfile(t_node *nodes, t_parsing *ps, int redir, t_shell *sh)
{
	int		try_open;

	try_open = 0;
	if (nodes[ps->i].outfiles)
		free(nodes[ps->i].outfiles);
	nodes[ps->i].outfiles = get_file_name(ps, nodes, 2);
	if (!nodes[ps->i].outfiles)
		ft_exit(sh, ps, nodes, "Fail to malloc outfiles in add_outfiles\n");
	nodes[ps->i].outfiles = remove_quotes_files(ps, nodes[ps->i].outfiles);
	if (!nodes[ps->i].outfiles)
		ft_exit(sh, ps, nodes, "Fail to malloc outfiles in add_outfiles\n");
	nodes[ps->i].append = redir;
	if (redir == 2)
		try_open = open(nodes[ps->i].outfiles,
				O_WRONLY | O_TRUNC | O_CREAT, 0644);
	else
		try_open = open(nodes[ps->i].outfiles,
				O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (try_open < 0)
		return (ret_err(0, NULL));
	close(try_open);
	return (1);
}

int	add_file(t_node *nodes, t_parsing *ps, int redir, t_shell *sh)
{
	if (redir == 1 && !nodes[ps->i].invalid_infile)
		add_infile(nodes, ps, sh);
	else if (redir == 1 && nodes[ps->i].invalid_infile)
		get_file_name(ps, nodes, 1);
	else if (redir == 2 || redir == 3)
		return (add_outfile(nodes, ps, redir, sh));
	return (1);
}
