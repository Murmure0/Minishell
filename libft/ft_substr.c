/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmasse <vmasse@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 10:05:08 by vmasse            #+#    #+#             */
/*   Updated: 2021/09/15 11:27:09 by vmasse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sample;
	size_t	i;
	int		len_s;

	if (!s)
		return (NULL);
	len_s = ft_strlen(s);
	if (len_s < (int)start)
		len = 0;
	else if (len_s < ((int)start + (int)len))
		len = len_s - start;
	sample = (char *)malloc((len + 1) * sizeof(char));
	if (!(sample))
		return (NULL);
	i = 0;
	while (i < len)
	{
		sample[i] = s[start];
		start++;
		i++;
	}
	sample[i] = '\0';
	return (sample);
}
