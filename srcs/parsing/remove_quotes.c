/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmasse <vmasse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 09:42:59 by vmasse            #+#    #+#             */
/*   Updated: 2022/03/03 10:39:32 by vmasse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*remove_quote(char *s, int pos)
{
	char	*before_quote;
	char	*tmp;

	before_quote = str_slice(s, 0, pos);
	if (!before_quote)
		return (NULL);
	tmp = ft_strjoin(before_quote, s + pos + 1);
	free(before_quote);
	free(s);
	return (tmp);
}

void	process_rm_quotes_cmd(t_parsing *ps, t_node *nodes)
{
	int		pos_quote;

	pos_quote = get_next_quote(ps, nodes[ps->i].cmd[ps->j], ps->k);
	while (pos_quote > -1)
	{
		set_quotes_for_cmd_in_quote(ps, nodes);
		if (!(ps->is_d_quote && ps->quote == '\'')
			&& !(ps->is_s_quote && ps->quote == '"'))
		{
				nodes[ps->i].cmd[ps->j] = remove_quote(
					nodes[ps->i].cmd[ps->j], pos_quote);
			ps->k = pos_quote;
		}
		else
			ps->k = pos_quote + 1;
		pos_quote = get_next_quote(ps, nodes[ps->i].cmd[ps->j], ps->k);
	}
}

void	remove_quotes_cmd(t_node *nodes, t_parsing *ps)
{
	ps->i = -1;
	while (++(ps->i) < ps->pipe_nb + 1)
	{
		ps->j = -1;
		while (nodes[ps->i].cmd[++(ps->j)])
		{
			ps->k = 0;
			set_quotes_for_cmd_in_quote(ps, nodes);
			process_rm_quotes_cmd(ps, nodes);
		}
	}
}

void	remove_quotes_files(t_parsing *ps)
{
	int		pos_quote;
	int		j;

	j = ps->j + 1;
	set_quotes_for_files_in_quote(ps, j);
	// printf("|%c| before : %d\n", ps->nodes[ps->i][j], ps->is_d_quote);
	pos_quote = get_next_quote(ps, ps->nodes[ps->i], j);
	while (pos_quote > -1)
	{
		set_quotes_for_files_in_quote(ps, j);
		// printf("|%c| after : %d\n", ps->nodes[ps->i][j], ps->is_d_quote);
		if ((!(ps->is_d_quote && ps->quote == '\'')
				&& !(ps->is_s_quote && ps->quote == '"')))
					ps->nodes[ps->i] = remove_quote(
					ps->nodes[ps->i], pos_quote);
		j = pos_quote + 1;
		pos_quote = get_next_quote(ps, ps->nodes[ps->i], j);
	}
	ps->is_d_quote = 0;
	ps->is_s_quote = 0;
}
