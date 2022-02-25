/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmasse <vmasse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 17:38:48 by vmasse            #+#    #+#             */
/*   Updated: 2022/02/24 17:41:51 by vmasse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static	int	count_elems(char const *s, char c)
{
	int	i;
	int	nb_elems;

	nb_elems = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			nb_elems++;
		i++;
	}
	return (nb_elems);
}

static	int	count_elem_len(char const *s, char c, int i)
{
	int	len;

	len = 0;
	while (s[i] && s[i] != c)
	{
		len++;
		i++;
	}
	return (len);
}

static	char	**free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
	return (NULL);
}

static	char	**fill_arr(char const *s, char **arr, char c)
{
	int	i;
	int	j;
	int	k;
	int	elem_len;

	i = -1;
	j = 0;
	while (s[++i])
	{
		if (s[i] != c)
		{
			k = 0;
			elem_len = count_elem_len(s, c, i);
			arr[j] = (char *)malloc((elem_len + 1) * sizeof(char));
			if (!arr[j])
				return (free_arr(arr));
			while (s[i] && s[i] != c)
				arr[j][k++] = s[i++];
			arr[j++][k] = '\0';
			arr[j] = '\0';
			if (!s[i])
				return (arr);
		}
	}
	return (arr);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	int		nb_elems;

	if (!s)
		return (NULL);
	nb_elems = count_elems(s, c);
	arr = (char **)malloc((nb_elems + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	arr[nb_elems] = 0;
	arr = fill_arr(s, arr, c);
	return (arr);
}
