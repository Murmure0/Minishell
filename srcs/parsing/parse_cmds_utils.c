/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmds_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmasse <vmasse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 11:38:50 by vmasse            #+#    #+#             */
/*   Updated: 2022/03/02 06:38:50 by vmasse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	set_quotes_for_prompt(t_parsing *ps)
{
	if (ps->nodes[ps->i][ps->j] == '\'')
	{
		if (ps->is_s_quote)
			ps->is_s_quote = 0;
		else
			ps->is_s_quote = 1;
	}
	else if (ps->nodes[ps->i][ps->j] == '"')
	{
		if (ps->is_d_quote)
			ps->is_d_quote = 0;
		else
			ps->is_d_quote = 1;
	}
}

void	get_cmds_nb_case_chevron(char *node, int *i)
{
	if (node[*i + 1] == '<' || node[*i + 1] == '>')
	{
		*i += 2;
		while (node[*i] && is_space(node[*i]))
			if (node[*i + 1])
				(*i)++;
		while (node[*i] && node[*i] != ' ' && node[*i] != '\t'
			&& node[*i] != '<' && node[*i] != '>')
			(*i)++;
	}
	if (node[*i] && node[*i + 1] && is_space(node[*i + 1]))
	{
		(*i)++;
		while (node[*i] && is_space(node[*i]))
			if (node[*i + 1])
				(*i)++;
	}
	while (node[*i] && (node[*i] != ' ' && node[*i] != '\t'))
		(*i)++;
}

void	set_quotes(t_parsing *ps, char *n, int *i)
{
	if (n[*i] == '\'')
	{
		if (ps->is_s_quote)
			ps->is_s_quote = 0;
		else
			ps->is_s_quote = 1;
		(*i)++;
	}
	else if (n[*i] == '"')
	{
		if (ps->is_d_quote)
			ps->is_d_quote = 0;
		else
			ps->is_d_quote = 1;
		(*i)++;
	}
}

int	get_cmds_nb(t_parsing *ps, char *node)
{
	int	i;
	int	nb;

	i = 0;
	nb = 0;
	while (node && node[i])
	{
		set_quotes(ps, node, &i);
		if ((!is_space(node[i]) && !is_chevron(node[i]))
			|| (is_space(node[i]) && (ps->is_d_quote || ps->is_s_quote))
				|| (is_chevron(node[i]) && (ps->is_d_quote || ps->is_s_quote)))
		{
			while ((node[i] && !is_space(node[i]))
					|| (is_space(node[i]) && (ps->is_d_quote || ps->is_s_quote)))
			{
				i++;
				set_quotes(ps, node, &i);
			}
			nb++;
		}
		else if (is_chevron(node[i]))
			get_cmds_nb_case_chevron(node, &i);
		if (node[i] && node[i + 1])
			i++;
		else
			break ;
	}
	return (nb);
}
