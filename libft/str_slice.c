/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_slice.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmasse <vmasse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 17:40:33 by vmasse            #+#    #+#             */
/*   Updated: 2022/02/24 17:40:35 by vmasse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*str_slice(char *src, int start, int stop)
{
	char	*string;
	int		src_size;
	int		i;

	if (!src)
		return (NULL);
	src_size = stop - start;
	string = malloc(sizeof(char) * (src_size + 1));
	if (!string)
		return (NULL);
	i = 0;
	while (start < stop)
	{
		string[i] = src[start];
		i++;
		start++;
	}
	string[src_size] = '\0';
	return (string);
}
