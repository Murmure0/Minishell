/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 18:43:23 by vmasse            #+#    #+#             */
/*   Updated: 2022/03/08 20:51:49 by mberthet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* renvoit la pos du 1er quote trouvé a partir de la position start, 
	ou -1 sil ne trouve pas */
int	get_quote_pos(t_parsing *parstruct, int start)
{
	while (parstruct->prompt[++start])
	{
		if (parstruct->prompt[start] == '"' || parstruct->prompt[start] == '\'')
			return (start);
	}
	return (-1);
}

/* renvoit la position du quote qui matche, 
	sinon renvoit 0 (pas possible davoir un matching quote a 0) */
int	get_matching_quote_pos(t_parsing *parstruct, int start)
{
	int	prev_quote;

	prev_quote = start;
	while (parstruct->prompt[++start])
	{
		if (parstruct->prompt[start] == parstruct->prompt[prev_quote])
			return (start);
	}
	return (0);
}

int	check_quotes_for_pipe_split(t_parsing *parstruct)
{
	int		pos_quote;
	int		has_to_match;

	pos_quote = get_quote_pos(parstruct, -1);
	if (pos_quote == -1)
		return (1);
	has_to_match = 1;
	while (pos_quote > -1 && parstruct->prompt[pos_quote])
	{
		if (has_to_match)
		{
			pos_quote = get_matching_quote_pos(parstruct, pos_quote);
			if (!pos_quote)
				return (ret_err(0, "minishell : error : Invalid syntax"));
			has_to_match = 0;
		}
		else
		{
			pos_quote = get_quote_pos(parstruct, pos_quote);
			has_to_match = 1;
		}
	}
	return (1);
}

int	get_next_quote_here(t_parsing *ps, char *s, int pos)
{
	(void)ps;
	if (pos > ft_strlen(s))
		return (-1);
	while (s && s[pos])
	{
		if ((s[pos] == '\'' && ps->is_s_quote) || (s[pos] == '"' && ps->is_d_quote))
			return (pos);
		pos++;
	}
	return (-1);

}

int	get_next_quote(t_parsing *ps, char *s, int pos)
{
	(void)ps;
	if (pos > ft_strlen(s))
		return (-1);
	while (s && s[pos])
	{
		if (s[pos] == '\'' || s[pos] == '"')
			return (pos);
		pos++;
	}
	return (-1);
}
