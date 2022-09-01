/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_quotes_two.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmasse <vmasse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 16:51:23 by vmasse            #+#    #+#             */
/*   Updated: 2022/03/10 16:51:50 by vmasse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	set_quotes_for_cmd_in_quote(t_parsing *ps, t_node *n)
{
	if (n[ps->i].cmd[ps->j][ps->k] == '\'' && !ps->is_d_quote)
	{
		ps->quote = '\'';
		if (ps->is_s_quote)
			ps->is_s_quote = 0;
		else
			ps->is_s_quote = 1;
	}
	else if (n[ps->i].cmd[ps->j][ps->k] == '"' && !ps->is_s_quote)
	{
		ps->quote = '"';
		if (ps->is_d_quote)
			ps->is_d_quote = 0;
		else
			ps->is_d_quote = 1;
	}
}

void	set_quotes_for_files_in_quote(t_parsing *ps,
		char *file, int *count_s, int *count_d)
{
	if (*count_d == 2 || *count_s == 2)
	{
		ps->is_d_quote = 0;
		ps->is_s_quote = 0;
		*count_d = 0;
		*count_s = 0;
	}
	if (file[ps->k] == '\'')
	{
		if (ps->is_s_quote)
			ps->quote = 0;
		else
			ps->is_s_quote = 1;
	}
	else if (file[ps->k] == '"')
	{
		if (ps->is_d_quote)
			ps->quote = 0;
		else
			ps->is_d_quote = 1;
	}
}

void	set_quotes_for_getfilename(t_parsing *ps,
		int j, int *count_s, int *count_d)
{
	(void)count_d;
	(void)count_s;
	if (ps->nodes[ps->i][j] == '\'')
	{
		if (ps->is_s_quote)
			ps->is_s_quote = 0;
		else
			ps->is_s_quote = 1;
	}
	else if (ps->nodes[ps->i][j] == '"')
	{
		if (ps->is_d_quote)
			ps->is_d_quote = 0;
		else
			ps->is_d_quote = 1;
	}
}

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
