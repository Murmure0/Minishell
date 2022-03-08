/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 09:42:59 by vmasse            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/03/08 10:31:22 by mberthet         ###   ########.fr       */
=======
/*   Updated: 2022/03/08 10:04:14 by vmasse           ###   ########.fr       */
>>>>>>> 147a7f142a2fe83ec0f622eb2ec247203b8b622d
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
			// printf("rm %d %d\n", ps->is_d_quote, ps->is_s_quote);
			set_quotes_for_cmd_in_quote(ps, nodes);
			// printf("|%s|\n", nodes[ps->i].cmd[ps->j]);
			process_rm_quotes_cmd(ps, nodes);
			// printf("|%s|\n", nodes[ps->i].cmd[ps->j]);
		}
	}
}

void	remove_quotes_files(t_parsing *ps)
{
	int		pos_quote;
	int		j;

	j = ps->j + 1;
	skip_spaces_local(ps, &j);
	set_quotes_for_files_in_quote(ps, j);
	pos_quote = get_next_quote(ps, ps->nodes[ps->i], j);
	// ps->nodes[ps->i] = remove_quote(ps->nodes[ps->i], pos_quote);
	// j = pos_quote;
	// pos_quote = get_next_quote(ps, ps->nodes[ps->i], j);
	while (pos_quote > -1)
	{
		if ((ps->nodes[ps->i][j] == '"' && (!ps->is_s_quote || ps->is_d_quote))
		|| (ps->nodes[ps->i][j] == '\'' && (!ps->is_d_quote || ps->is_s_quote)))
		{
					ps->nodes[ps->i] = remove_quote(
					ps->nodes[ps->i], pos_quote);
		}
		j = pos_quote;
		printf("|%c| while : %d\n", ps->nodes[ps->i][j], ps->is_d_quote);
		if ((!ps->is_d_quote && !ps->is_s_quote) && (!is_quote(ps->nodes[ps->i][j])
				|| is_space(ps->nodes[ps->i][j])))
		{
			printf("|%c| break at : %d\n", ps->nodes[ps->i][j], ps->is_d_quote);
			break ;
		}
		set_quotes_for_files_in_quote(ps, j);
		pos_quote = get_next_quote(ps, ps->nodes[ps->i], j);
	}
	printf("|%s| after : %d\n", ps->nodes[ps->i], ps->is_d_quote);
	ps->is_d_quote = 0;
	ps->is_s_quote = 0;
}
