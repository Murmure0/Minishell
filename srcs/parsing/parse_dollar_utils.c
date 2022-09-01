/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dollar_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 10:27:40 by vmasse            #+#    #+#             */
/*   Updated: 2022/03/09 14:18:01 by mberthet         ###   ########.fr       */
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
