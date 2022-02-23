/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmasse <vmasse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 16:29:40 by vmasse            #+#    #+#             */
/*   Updated: 2022/02/23 15:36:15 by vmasse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include <stdio.h>

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

static	int	count_elem_len(char const *s, char c, int i, int is_quote)
{
	int	len;

	len = 0;
	while (s[i] && (s[i] != c || is_quote))
	{
		if (s[i] == '\'' || s[i] == '"')
		{
			if (is_quote)
				is_quote = 0;
			else
				is_quote = 1;
		}
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

static	char	**fill_arr(char const *s, char **arr, char c, int is_quote)
{
	int	i;
	int	j;
	int	k;
	int	elem_len;

	set_i_and_j(&i, &j);
	while (s[++i])
	{
		if (s[i] != c)
		{
			k = 0;
			elem_len = count_elem_len(s, c, i, is_quote);
			arr[j] = (char *)malloc((elem_len + 1) * sizeof(char));
			if (!arr[j])
				return (free_arr(arr));
			while (s[i] && (s[i] != c || is_quote))
			{
				set_quote(s[i], &is_quote);
				arr[j][k++] = s[i++];
			}
			arr[j++][k] = '\0';
			arr[j] = '\0';
			if (!s[i])
				return (arr);
		}
	}
	return (arr);
}

char	**ft_split_pipe(char const *s, char c)
{
	char	**arr;
	int		nb_elems;
	int		is_quote;

	if (!s)
		return (NULL);
	is_quote = 0;
	nb_elems = count_elems(s, c);
	arr = (char **)malloc((nb_elems + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	arr[nb_elems] = 0;
	arr = fill_arr(s, arr, c, is_quote);
	return (arr);
}
