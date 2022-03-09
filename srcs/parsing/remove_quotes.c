/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 09:42:59 by vmasse            #+#    #+#             */
/*   Updated: 2022/03/09 17:30:29 by mberthet         ###   ########.fr       */
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
	// printf("contenu tmp : %s\n", tmp);
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
			// printf("This quote is a problem : %c\n", nodes[ps->i].cmd[ps->j][ps->k]);
			// printf("dquote : %d	squote : %d\n", ps->is_d_quote, ps->is_s_quote);
			nodes[ps->i].cmd[ps->j] = remove_quote(
				nodes[ps->i].cmd[ps->j], ps->k);
			ps->k = get_next_quote(ps, nodes[ps->i].cmd[ps->j], ps->k);
		}
		else
			ps->k = get_next_quote(ps, nodes[ps->i].cmd[ps->j], ps->k+1);
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
			//printf("|%s|\n", nodes[ps->i].cmd[ps->j]);
		}
	}
}

void	remove_quotes_files(t_parsing *ps)
{
	int		pos_quote;
	int		j;
	int		count_s = 0;
	int		count_d = 0;

	j = ps->j;
	if (ps->nodes[ps->i][ps->j] == '>')
		j++;
	skip_spaces_local(ps, &j);
	printf("CHAR : %c\n", ps->nodes[ps->i][j]);
	set_quotes_for_files_in_quote(ps, j, &count_s, &count_d);
	pos_quote = get_next_quote(ps, ps->nodes[ps->i], j);
	while (pos_quote > -1)
	{
		if ((!(ps->is_d_quote && ps->is_s_quote)
			|| ((ps->is_d_quote && ps->is_s_quote)
			&& ((ps->nodes[ps->i][j] == '"' && count_d)
			|| (ps->nodes[ps->i][j] == '\'' && count_s))))
			&& ((ps->nodes[ps->i][j] == '"')
			|| (ps->nodes[ps->i][j] == '\''))) //faire une fonction pour ca, bisou <3
		{
					if (ps->nodes[ps->i][j] == '"')
						count_d++;
					if (ps->nodes[ps->i][j] == '\'')
						count_s++;
					ps->nodes[ps->i] = remove_quote(ps->nodes[ps->i], pos_quote);
					j = pos_quote;
		}
		else
			j = pos_quote + 1;
		if ((!ps->is_d_quote && !ps->is_s_quote) && (!is_quote(ps->nodes[ps->i][j])
				|| is_space(ps->nodes[ps->i][j])))
		{
			break ;
		}
		pos_quote = get_next_quote(ps, ps->nodes[ps->i], j);
		j = pos_quote;
		if (j > -1)
			set_quotes_for_files_in_quote(ps, j, &count_s, &count_d);
	}
	ps->is_d_quote = 0;
	ps->is_s_quote = 0;
}



