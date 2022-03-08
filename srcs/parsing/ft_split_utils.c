/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 16:16:28 by vmasse            #+#    #+#             */
/*   Updated: 2022/03/08 15:29:13 by mberthet         ###   ########.fr       */
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

void	init_struct(t_split *st)
{
	st->i = -1;
	st->j = 0;
	st->k = 0;
	st->is_quote = 0;
}

int	check_end(t_split *st, char const *s, char **arr)
{
	// printf("i : %d	j : %d	len : %d\n", st->i, st->j, ft_strlen(s)); //DELETE ME LATER
	if (!s[st->i])
	{
		arr[st->j] = NULL;
		return (0);
	}
	return (1);
}
