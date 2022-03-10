/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_quotes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 07:19:26 by vmasse            #+#    #+#             */
/*   Updated: 2022/03/10 10:09:31 by mberthet         ###   ########.fr       */
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

void	set_quotes_for_files_in_quote(t_parsing *ps, char *file, int *count_s, int *count_d)
{
	// (void)count;
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
		{
			ps->quote = 0;
			// ps->is_s_quote = 0;
		}
		else
		{
			ps->quote = '\'';
			ps->is_s_quote = 1;
		}
	}
	else if (file[ps->k] == '"')
	{
		if (ps->is_d_quote)
		{
			ps->quote = 0;
			// ps->is_d_quote = 0;
		}
		else
		{
			ps->quote = '"';
			ps->is_d_quote = 1;
		}
	}
}

int	is_quote(char c)
{
	if (c == '"' || c == '\'')
		return (1);
	return (0);
}