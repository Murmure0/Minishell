/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmasse <vmasse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 18:43:23 by vmasse            #+#    #+#             */
/*   Updated: 2022/01/20 21:03:13 by vmasse           ###   ########.fr       */
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

void	check_quotes_for_pipe_split(t_parsing *parstruct)
{
	int		pos_quote;
	int		has_to_match;
	t_shell	g_shell;

	pos_quote = get_quote_pos(parstruct, -1);
	if (pos_quote == -1)
		return ;
	has_to_match = 1;
	while (pos_quote > -1 && parstruct->prompt[pos_quote])
	{
		if (has_to_match)
		{
			pos_quote = get_matching_quote_pos(parstruct, pos_quote);
			if (!pos_quote)
				ft_exit(g_shell);
			has_to_match = 0;
		}
		else
		{
			pos_quote = get_quote_pos(parstruct, pos_quote);
			has_to_match = 1;
		}
	}
}
