/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmasse <vmasse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 16:07:11 by vmasse            #+#    #+#             */
/*   Updated: 2022/03/10 16:55:19 by vmasse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_removable(t_parsing *ps, char *file, int count_d, int count_s)
{
	if ((!(ps->is_d_quote && ps->is_s_quote)
			|| ((ps->is_d_quote && ps->is_s_quote)
				&& ((file[ps->k] == '"' && count_d)
					|| (file[ps->k] == '\'' && count_s))))
		&& ((file[ps->k] == '"')
			|| (file[ps->k] == '\'')))
		return (1);
	return (0);
}

void	init_var_rm_quotes_files(t_parsing *ps, int *s, int *d)
{
	ps->k = 0;
	*s = 0;
	*d = 0;
}

void	increment_quotes_count(char c, int *d, int *s)
{
	if (c == '"')
		(*d)++;
	if (c == '\'')
		(*s)++;
}

int	gnq_rm_quotes_files(int *pos_quote, t_parsing *ps, char *file)
{
	*pos_quote = get_next_quote(ps, file, ps->k);
	ps->k = *pos_quote;
	if (ps->k > -1)
		return (1);
	return (0);
}

char	*end_rm_quotes_files(t_parsing *ps, char *file)
{
	init_quote_states(ps);
	ps->k = 0;
	return (file);
}
