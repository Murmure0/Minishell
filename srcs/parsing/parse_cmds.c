/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmasse <vmasse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 16:25:17 by vmasse            #+#    #+#             */
/*   Updated: 2022/03/02 07:43:35 by vmasse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_for_command_args(t_parsing *ps, int *pos_start, int *stop)
{
	skip_spaces(ps);
	*pos_start = ps->j;
	if (!ps->nodes[ps->i][ps->j])
		return (0);
	ps->pos_tmp = ps->j;
	set_quotes_for_prompt(ps);
	if (ps->nodes[ps->i][ps->j] == '"' || ps->nodes[ps->i][ps->j] == '\'')
		ps->j++;
	while (ps->nodes[ps->i][ps->j] && (!is_space(ps->nodes[ps->i][ps->j])
		|| (ps->is_d_quote && ps->nodes[ps->i][ps->j] != '"')
			|| (ps->is_s_quote && ps->nodes[ps->i][ps->j] != '\'')))
	{
		set_quotes_for_prompt(ps);
		if (is_chevron(ps->nodes[ps->i][ps->j])
			&& !ps->is_d_quote && !ps->is_s_quote)
		{
			*stop = 1;
			break ;
		}
		ps->j++;
	}
	return (1);
}

int	add_cmd_args_case_stop(t_parsing *ps, t_node **n, t_shell *sh, int pos)
{
	if (ps->pos_tmp != ps->j)
	{
		(*n)[ps->i].cmd[ps->pos_cmd] = str_slice(ps->nodes[ps->i],
				pos, ps->j);
		if (!(*n)[ps->i].cmd[ps->pos_cmd])
			ft_exit(sh, ps, *n, "Fail to malloc args in add_cmd stop\n");
	}
	else
		(*n)[ps->i].cmd[ps->cmd_nb] = 0;
	return (1);
}

void	add_command_args(t_node **nodes, t_parsing *ps, t_shell *sh)
{
	int		pos_start;
	int		stop;

	stop = 0;
	while (ps->nodes[ps->i][ps->j] && (!is_chevron(ps->nodes[ps->i][ps->j])
			|| (ps->is_d_quote || ps->is_s_quote)))
	{
		if (!check_for_command_args(ps, &pos_start, &stop))
			return ;
		if (stop)
			if (add_cmd_args_case_stop(ps, nodes, sh, pos_start))
				return ;
		(*nodes)[ps->i].cmd[ps->pos_cmd] = str_slice(ps->nodes[ps->i],
				pos_start, ps->j);
		if (!(*nodes)[ps->i].cmd[ps->pos_cmd])
			ft_exit(sh, ps, *nodes, "Fail to malloc args in add_command_args\n");
		ps->pos_cmd++;
		if (ps->nodes[ps->i][ps->j] && ps->nodes[ps->i][ps->j + 1])
			ps->j++;
		else
			break ;
	}
	(*nodes)[ps->i].cmd[ps->cmd_nb] = 0;
}

void	add_command(t_node **nodes, t_parsing *ps, t_shell *sh)
{
	int		pos_start;

	skip_spaces(ps);
	pos_start = ps->j;
	while (ps->nodes[ps->i][ps->j])
	{
		set_quotes_for_prompt(ps);
		if ((is_space(ps->nodes[ps->i][ps->j])
			|| is_chevron(ps->nodes[ps->i][ps->j]))
			&& !ps->is_s_quote && !ps->is_d_quote)
			break ;
		ps->j++;
	}
	(*nodes)[ps->i].cmd[ps->pos_cmd] = str_slice(ps->nodes[ps->i],
			pos_start, ps->j);
	if (!(*nodes)[ps->i].cmd[ps->pos_cmd])
		ft_exit(sh, ps, *nodes, "Fail to malloc nodes cmd in add_command\n");
	ps->pos_cmd++;
	add_command_args(nodes, ps, sh);
}
