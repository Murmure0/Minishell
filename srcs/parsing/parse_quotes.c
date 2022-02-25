/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmasse <vmasse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 18:43:23 by vmasse            #+#    #+#             */
/*   Updated: 2022/02/25 14:47:26 by vmasse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* renvoit la pos du 1er quote trouvé a partir de la position start, 
	ou -1 sil ne trouve pas */
int	get_quote_pos(t_parsing *parstruct, int start)
{
	while (parstruct->prompt[++start])
	{
		if (parstruct->prompt[start] == '"' || parstruct->prompt[start] == '\'')
			return (start);
	}
	return (-1);
}

/* renvoit la position du quote qui matche, 
	sinon renvoit 0 (pas possible davoir un matching quote a 0) */
int	get_matching_quote_pos(t_parsing *parstruct, int start)
{
	int	prev_quote;

	prev_quote = start;
	while (parstruct->prompt[++start])
	{
		if (parstruct->prompt[start] == parstruct->prompt[prev_quote])
			return (start);
	}
	return (0);
}

int	check_quotes_for_pipe_split(t_parsing *parstruct)
{
	int		pos_quote;
	int		has_to_match;

	pos_quote = get_quote_pos(parstruct, -1);
	if (pos_quote == -1)
		return (1);
	has_to_match = 1;
	while (pos_quote > -1 && parstruct->prompt[pos_quote])
	{
		if (has_to_match)
		{
			pos_quote = get_matching_quote_pos(parstruct, pos_quote);
			if (!pos_quote)
				return (ret_err(0, "minishell : error : Invalid syntax"));
			has_to_match = 0;
		}
		else
		{
			pos_quote = get_quote_pos(parstruct, pos_quote);
			has_to_match = 1;
		}
	}
	return (1);
}

int	get_next_quote(t_parsing *ps, char *s, int pos)
{
	(void)ps;
	while (s && s[pos])
	{
		if (s[pos] == '\'' || s[pos] == '"')
			return (pos);
		pos++;
	}
	return (-1);
}

char	*remove_quote(char *s, int pos, t_parsing *ps)
{
	char	*before_quote;
	char	*tmp;

	// printf("CMD INSIDE : %s\n", s);
	before_quote = str_slice(s, 0, pos);
	if (!before_quote)
		return (NULL);
	tmp = ft_strjoin(before_quote, s + pos + 1);
	free(before_quote);
	free(s);
	ps->quote = 0;
	return (tmp);
}

void	set_quotes_for_cmd_in_quote(t_parsing *ps, t_node *n)
{
	if (n[ps->i].cmd[ps->j][ps->k] == '\'')
	{
		ps->quote = '\'';
		// printf("found s quote at %d\n", ps->k);
		if (ps->is_s_quote)
			ps->is_s_quote = 0;
		else
			ps->is_s_quote = 1;
	}
	else if (n[ps->i].cmd[ps->j][ps->k] == '"')
	{
		ps->quote = '"';
		// printf("found d quote at %d\n", ps->k);
		if (ps->is_d_quote)
			ps->is_d_quote = 0;
		else
			ps->is_d_quote = 1;
	}
}

void	remove_quotes_cmd(t_node *nodes, t_parsing *ps)
{
	int		pos_quote;

	ps->i = -1;
	while (++(ps->i) < ps->pipe_nb + 1)
	{
		ps->j = -1;
		while (nodes[ps->i].cmd[++(ps->j)])
		{
			ps->k = 0;
			pos_quote = get_next_quote(ps, nodes[ps->i].cmd[ps->j], ps->k);
			while (pos_quote > -1)
			{
				set_quotes_for_cmd_in_quote(ps, nodes);
				if ((!(ps->is_d_quote && ps->quote == '\'')
					&& !(ps->is_s_quote && ps->quote == '"'))
					|| ((ps->is_d_quote && ps->quote == '"') && (ps->is_s_quote && ps->quote == '\'')))
				{
					nodes[ps->i].cmd[ps->j] = remove_quote(nodes[ps->i].cmd[ps->j], pos_quote, ps);
					ps->k = pos_quote;
				}
				else if (ps->quote)
					ps->k = pos_quote + 1;
				pos_quote = get_next_quote(ps, nodes[ps->i].cmd[ps->j], ps->k);
			}
			printf("CMD : %s\n", nodes[ps->i].cmd[ps->j]);
		}
	}
}
