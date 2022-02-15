/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmasse <vmasse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 16:25:17 by vmasse            #+#    #+#             */
/*   Updated: 2022/02/11 18:28:28 by vmasse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

int	get_cmds_nb(char *node)
{
	int	i;
	int	nb;

	i = 0;
	nb = 0;
	while (node && node[i])
	{
		if (node[i] != ' ' && node[i] != '\t'
			&& node[i] != '<' && node[i] != '>')
		{
			while (node[i] && (node[i] != ' ' && node[i] != '\t'))
				i++;
			nb++;
		}
		else if (node[i] == '<' || node[i] == '>')
			get_cmds_nb_case_chevron(node, &i);
		if (node[i] && node[i + 1])
			i++;
		else
			break ;
	}
	return (nb);
}

int	check_for_command_args(t_parsing *ps, int *pos_start, int *stop)
{
	skip_spaces(ps);
	*pos_start = ps->j;
	if (!ps->nodes[ps->i][ps->j])
		return (0);
	while (ps->nodes[ps->i][ps->j] && ps->nodes[ps->i][ps->j] != '\t'
		&& ps->nodes[ps->i][ps->j] != ' ')
	{
		if (is_chevron(ps->nodes[ps->i][ps->j]))
		{
			*stop = 1;
			break ;
		}
		ps->j++;
	}
	return (1);
}

void	add_command_args(t_node **nodes, t_parsing *ps, t_shell *sh)
{
	int		pos_start;
	int		stop;

	stop = 0;
	while (ps->nodes[ps->i][ps->j] && ps->nodes[ps->i][ps->j] != '<'
		&& ps->nodes[ps->i][ps->j] != '>')
	{
		if (!check_for_command_args(ps, &pos_start, &stop))
			return ;
		if (stop)
		{
			(*nodes)[ps->i].cmd[ps->cmd_nb] = 0;
			return ;
		}
		(*nodes)[ps->i].cmd[ps->pos_cmd] = str_slice(ps->nodes[ps->i],
				pos_start, ps->j);
		if (!(*nodes)[ps->i].cmd[ps->pos_cmd])
			ft_exit(sh, ps, *nodes, "Fail to malloc args in add_command_args\n");
		if (ps->nodes[ps->i][ps->j] && ps->nodes[ps->i][ps->j + 1])
			ps->j++;
		else
			break ;
		ps->pos_cmd++;
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
		if (is_space(ps->nodes[ps->i][ps->j])
			|| is_chevron(ps->nodes[ps->i][ps->j]))
			break ;
		ps->j++;
	}
	expand_dollar_value(*nodes, ps, sh, pos_start);
	printf("%s\n", (*nodes)[ps->i].cmd[ps->pos_cmd]);
	// (*nodes)[ps->i].cmd[ps->pos_cmd] = str_slice(ps->nodes[ps->i],
	// 		pos_start, ps->j);
	// if (!(*nodes)[ps->i].cmd[ps->pos_cmd])
	// 	ft_exit(sh, ps, *nodes, "Fail to malloc nodes cmd in add_command\n");
	ps->pos_cmd++;
	add_command_args(nodes, ps, sh);
}
