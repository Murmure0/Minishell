/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmasse <vmasse@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 09:28:59 by vmasse            #+#    #+#             */
/*   Updated: 2021/09/15 11:27:02 by vmasse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s3;
	int		i;
	int		len;

	if (!s1 || !s2)
		return (NULL);
	s3 = (char *)malloc(sizeof(char) * (ft_strlen((char *)s1) + \
	ft_strlen((char *)s2) + 1));
	if (!(s3))
		return (NULL);
	i = -1;
	while (s1[++i])
		s3[i] = s1[i];
	s3[i] = '\0';
	i = -1;
	len = ft_strlen(s3);
	while (s2[++i])
		s3[len + i] = s2[i];
	s3[len + i] = '\0';
	return (s3);
}
