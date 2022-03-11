/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmasse <vmasse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 17:40:14 by vmasse            #+#    #+#             */
/*   Updated: 2022/03/11 10:09:42 by vmasse           ###   ########.fr       */
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

static int	is_inset(char const *set, char c)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*s2;
	int		i;
	int		j;
	int		k;

	i = 0;
	k = 0;
	if (!s1 || !set)
		return (NULL);
	while (is_inset(set, s1[i]))
		i++;
	j = ft_strlen(s1) - 1;
	while (j > i && is_inset(set, s1[j]))
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
