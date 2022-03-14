/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmasse <vmasse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 07:10:31 by vmasse            #+#    #+#             */
/*   Updated: 2022/03/14 13:20:00 by vmasse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_exit_st;

int	check_empty_before_pipe(char *s)
{
	int	i;

	i = -1;
	while (s[++i] && s[i] != '|')
	{
		if (!is_space(s[i]))
		{
			return (0);
		}
	}
	return (1);
}

int	check_empty_pipe(t_parsing *ps)
{
	while (++(ps->i) <= ps->pipe_nb)
	{
		if (!ps->nodes[ps->i] || check_empty_before_pipe(ps->nodes[ps->i]))
		{
			write(2, "minishell: syntax error near unexpected token `|'\n", 51);
			g_exit_st = 2;
			return (0);
		}
	}
	return (1);
}
