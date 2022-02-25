/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr_pos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmasse <vmasse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 08:25:16 by vmasse            #+#    #+#             */
/*   Updated: 2022/02/24 17:39:20 by vmasse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_strchr_pos(char *s, char c, int pos)
{
	while (s[++pos] != (char)c)
		if (!s[pos])
			return (-1);
	return (pos);
}
