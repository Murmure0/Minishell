/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmasse <vmasse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 09:42:59 by vmasse            #+#    #+#             */
/*   Updated: 2022/03/10 16:43:34 by vmasse           ###   ########.fr       */
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
	ps->k = 0;
	ps->is_s_quote = 0;
	ps->is_d_quote = 0;
	ps->k = get_next_quote(ps, nodes[ps->i].cmd[ps->j], ps->k);
	while (ps->k > -1)
	{
		set_quotes_for_cmd_in_quote(ps, nodes);
		if ((!ps->is_d_quote && nodes[ps->i].cmd[ps->j][ps->k] == '\'')
			|| (!ps->is_s_quote && nodes[ps->i].cmd[ps->j][ps->k] == '"'))
		{
			nodes[ps->i].cmd[ps->j] = remove_quote(
					nodes[ps->i].cmd[ps->j], ps->k);
			ps->k = get_next_quote(ps, nodes[ps->i].cmd[ps->j], ps->k);
		}
		else
			ps->k = get_next_quote(ps, nodes[ps->i].cmd[ps->j], ps->k + 1);
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

static int	protect_file_malloc(char **file, int pos_quote)
{
	*file = remove_quote(*file, pos_quote);
	if (!*file)
		return (0);
	return (1);
}

char	*remove_quotes_files(t_parsing *ps, char *file)
{
	int		pos_quote;
	int		count_s;
	int		count_d;

	init_var_rm_quotes_files(ps, &count_s, &count_d);
	set_quotes_for_files_in_quote(ps, file, &count_s, &count_d);
	pos_quote = get_next_quote(ps, file, ps->k);
	while (pos_quote > -1)
	{
		if (is_removable(ps, file, count_d, count_s))
		{
			increment_quotes_count(file[ps->k], &count_d, &count_s);
			if (!protect_file_malloc(&file, pos_quote))
				return (NULL);
			ps->k = pos_quote;
		}
		else
			ps->k = pos_quote + 1;
		if ((!ps->is_d_quote && !ps->is_s_quote) && (!is_quote(file[ps->k])
				|| is_space(file[ps->k])))
			break ;
		if (gnq_rm_quotes_files(&pos_quote, ps, file))
			set_quotes_for_files_in_quote(ps, file, &count_s, &count_d);
	}
	return (end_rm_quotes_files(ps, file));
}
