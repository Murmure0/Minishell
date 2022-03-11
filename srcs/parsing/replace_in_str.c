/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_in_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmasse <vmasse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 16:55:33 by vmasse            #+#    #+#             */
/*   Updated: 2022/03/11 16:56:01 by vmasse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*replace_in_str(char *s, char *value, int pos, int len)
{
	char	*before_dollar;
	char	*tmp;
	char	*tmp_two;
	char	*ret;

	before_dollar = str_slice(s, 0, pos);
	if (!before_dollar)
		return (NULL);
	tmp = ft_strjoin(before_dollar, value);
	free(before_dollar);
	if (!tmp)
		return (NULL);
	tmp_two = ft_strdup(s);
	if (!tmp_two)
	{
		free(tmp);
		return (NULL);
	}
	ret = ft_strjoin(tmp, tmp_two + pos + len + 1);
	free(tmp);
	free(tmp_two);
	return (ret);
}
