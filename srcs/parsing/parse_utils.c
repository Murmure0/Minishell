/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmasse <vmasse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 17:08:35 by vmasse            #+#    #+#             */
/*   Updated: 2022/03/11 16:55:44 by vmasse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	arr_len(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
	{
		i++;
	}
	return (i);
}

int	check_space_between_redirs(t_parsing *ps)
{
	int	j;

	j = ps->j;
	if (is_space(ps->nodes[ps->i][j]))
	{
		j++;
		while (ps->nodes[ps->i][j] && is_space(ps->nodes[ps->i][j]))
		{
			if (ps->nodes[ps->i][j + 1])
				j++;
			else
				break ;
		}
		if (ps->nodes[ps->i][j] && is_chevron(ps->nodes[ps->i][j]))
		{
			printf("minishell: syntax error near unexpected token `%c'\n",
				ps->nodes[ps->i][j]);
			return (0);
		}
	}
	return (1);
}

void	skip_spaces(t_parsing *ps)
{
	while (ps->nodes[ps->i][ps->j] && is_space(ps->nodes[ps->i][ps->j]))
	{
		if (ps->nodes[ps->i][ps->j + 1])
			ps->j++;
		else
			break ;
	}
}

void	end_parse(t_parsing *ps, t_node *nodes, t_shell *sh)
{
	if (ps->cmd_nb)
	{
		expand_dollar_value_cmd(nodes, ps, sh);
		remove_quotes_cmd(nodes, ps);
	}
}

void	init_quote_states(t_parsing *ps)
{
	ps->is_d_quote = 0;
	ps->is_s_quote = 0;
}
