/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmds_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmasse <vmasse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 11:38:50 by vmasse            #+#    #+#             */
/*   Updated: 2022/03/10 15:24:13 by vmasse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	case_chevron(char *node, int *i, t_parsing *ps)
{
	if (node[*i] && node[*i + 1] && (is_space(node[*i])
			|| is_space(node[*i + 1])) && !ps->is_d_quote && !ps->is_s_quote)
	{
		(*i)++;
		while (node[*i] && is_space(node[*i]))
			if (node[*i + 1])
				(*i)++;
	}
	while (node[*i] && ((node[*i] != ' ' && node[*i] != '\t')
			|| ps->is_d_quote || ps->is_s_quote))
	{
		set_quotes_without_move(ps, node, *i);
		(*i)++;
	}
}

void	get_cmds_nb_case_chevron(char *node, int *i, t_parsing *ps)
{
	if ((node[*i] == '<' && node[*i + 1] != '<')
		|| (node[*i] == '>' && node[*i + 1] != '>'))
		(*i)++;
	else if (node[*i + 1] == '<' || node[*i + 1] == '>')
	{
		(*i)++;
		while (node[*i] && is_space(node[*i]))
			if (node[*i + 1])
				(*i)++;
		while (node[*i] && node[*i] != ' ' && node[*i] != '\t'
			&& node[*i] != '<' && node[*i] != '>'
			&& !ps->is_d_quote && !ps->is_s_quote)
		{
			set_quotes_without_move(ps, node, *i);
			(*i)++;
		}
	}
	case_chevron(node, i, ps);
}

void	process_get_cmds_nb(t_parsing *ps, char *node, int *i)
{
	while ((node[*i] && !is_space(node[*i]))
		|| (is_space(node[*i]) && (ps->is_d_quote
				|| ps->is_s_quote)))
	{
		(*i)++;
		set_quotes(ps, node, i);
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
			process_get_cmds_nb(ps, node, &i);
			nb++;
		}
		else if (is_chevron(node[i]))
			get_cmds_nb_case_chevron(node, &i, ps);
		if (node[i] && node[i + 1])
			i++;
		else
			break ;
	}
	return (nb);
}
