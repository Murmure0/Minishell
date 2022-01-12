/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmasse <vmasse@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 16:23:42 by vmasse            #+#    #+#             */
/*   Updated: 2021/09/15 11:26:50 by vmasse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*buffer;

	buffer = (char *)s;
	i = 0;
	while (i < n)
	{
		buffer[i] = '\0';
		i++;
	}
	s = (void *)buffer;
}
