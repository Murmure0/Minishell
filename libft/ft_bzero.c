/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmasse <vmasse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 17:38:20 by vmasse            #+#    #+#             */
/*   Updated: 2022/02/24 17:38:22 by vmasse           ###   ########.fr       */
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
