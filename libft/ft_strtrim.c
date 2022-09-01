/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmasse <vmasse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 17:40:14 by vmasse            #+#    #+#             */
/*   Updated: 2022/03/14 13:05:42 by vmasse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static void	*ft_memalloc_trim(size_t size)
{
	void	*allocated_area;

	allocated_area = malloc(size);
	if (!allocated_area)
		return (NULL);
	ft_bzero(allocated_area, size);
	return (allocated_area);
}

static char	*ft_strnew_trim(size_t size)
{
	return ((char *)ft_memalloc_trim((size + 1) * (sizeof(char))));
}

char	*ft_strtrim(char const *s1, char c)
{
	char	*s2;
	int		i;
	int		j;
	int		k;

	i = 0;
	k = 0;
	if (!s1 || !c)
		return (NULL);
	while (s1[i] == c)
		i++;
	j = ft_strlen(s1) - 1;
	while (j > i && s1[j] == c)
		j--;
	if (ft_strlen(s1) == i)
		return (ft_strdup(""));
	s2 = ft_strnew_trim((j - i) + 1);
	if (!(s2))
		return (NULL);
	while (i <= j)
		s2[k++] = s1[i++];
	return (s2);
}
