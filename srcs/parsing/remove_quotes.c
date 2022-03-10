/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmasse <vmasse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 09:42:59 by vmasse            #+#    #+#             */
/*   Updated: 2022/03/10 12:16:42 by vmasse           ###   ########.fr       */
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

char	*remove_quotes_files(t_parsing *ps, char *file)
{
	int		pos_quote;
	int		count_s = 0;
	int		count_d = 0;

	ps->k = 0;
	if (file[ps->k] == '>' || file[ps->k] == '<')
		ps->k++;
	// printf("CHAR : %c\n", ps->nodes[ps->i][ps->k]);
	set_quotes_for_files_in_quote(ps, file, &count_s, &count_d);
	pos_quote = get_next_quote(ps, file, ps->k);
	while (pos_quote > -1)
	{
		if ((!(ps->is_d_quote && ps->is_s_quote)
			|| ((ps->is_d_quote && ps->is_s_quote)
			&& ((file[ps->k] == '"' && count_d)
			|| (file[ps->k] == '\'' && count_s))))
			&& ((file[ps->k] == '"')
			|| (file[ps->k] == '\''))) //faire une fonction pour ca, bisou <3
		{
					if (file[ps->k] == '"')
						count_d++;
					if (file[ps->k] == '\'')
						count_s++;
					file = remove_quote(file, pos_quote);
					ps->k = pos_quote;
		}
		else
			ps->k = pos_quote + 1;
		if ((!ps->is_d_quote && !ps->is_s_quote) && (!is_quote(file[ps->k])
				|| is_space(file[ps->k])))
		{
			break ;
		}
		pos_quote = get_next_quote(ps, file, ps->k);
		ps->k = pos_quote;
		if (ps->k > -1)
			set_quotes_for_files_in_quote(ps, file, &count_s, &count_d);
	}
	printf("ici : %s\n", file);
	ps->is_d_quote = 0;
	ps->is_s_quote = 0;
	ps->k = 0;
	return (file);
}



