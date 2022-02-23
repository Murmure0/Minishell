/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmasse <vmasse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 16:16:28 by vmasse            #+#    #+#             */
/*   Updated: 2022/02/23 14:26:28 by vmasse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	set_quote(char c, int *is_quote)
{
	if (c == '\'' || c == '"')
	{
		if (*is_quote)
			*is_quote = 0;
		else
			*is_quote = 1;
	}
}

void	set_i_and_j(int *i, int *j)
{
	*i = -1;
	*j = 0;
}

int	put_arr_end(char ***arr, int *j, int k, char s)
{
	*arr[*j++][k] = '\0';
	if (!s)
		return (0);
	return (1);
}
