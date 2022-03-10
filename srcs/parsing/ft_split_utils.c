/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmasse <vmasse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 16:16:28 by vmasse            #+#    #+#             */
/*   Updated: 2022/03/10 15:15:59 by vmasse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	set_quote(char c, t_split *st)
{
	if (c == '\'' || c == '"')
	{
		if (st->is_quote)
			st->is_quote = 0;
		else
			st->is_quote = 1;
	}
}

void	set_quote_utils(char c, t_split *st)
{
	if (!st->is_quote && c == '\'')
		st->is_quote = 1;
	else if (!st->is_quote && c == '"')
		st->is_quote = 2;
	else if ((st->is_quote == 1 && c == '\'')
		|| (st->is_quote == 2 && c == '"'))
		st->is_quote = 0;
	return ;
}

void	init_struct(t_split *st)
{
	st->i = -1;
	st->j = 0;
	st->k = 0;
	st->is_quote = 0;
}

int	check_end(t_split *st, char const *s, char **arr)
{
	if (!s[st->i])
	{
		arr[st->j] = NULL;
		return (0);
	}
	return (1);
}
