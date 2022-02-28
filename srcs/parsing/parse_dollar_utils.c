/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dollar_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmasse <vmasse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 10:27:40 by vmasse            #+#    #+#             */
/*   Updated: 2022/02/28 12:13:09 by vmasse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_value_tmp(char *value, char *tmp)
{
	free(value);
	free(tmp);
}

int	get_key_len(char *s, int pos)
{
	int	len;

	len = 0;
	while (s[pos] && (ft_isalnum(s[pos]) || s[pos] == '_'))
	{
		len++;
		pos++;
	}
	return (len);
}
