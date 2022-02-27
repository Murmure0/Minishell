/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmasse <vmasse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 16:29:40 by vmasse            #+#    #+#             */
/*   Updated: 2022/02/27 18:35:44 by vmasse           ###   ########.fr       */
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

static	int	count_elem_len(char const *s, char c, int i, int is_quote)
{
	int	len;

	len = 0;
	while (s[i] && (s[i] != c || is_quote))
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

static	char	**fill_arr(char const *s, char **arr, char c, t_split *st)
{
	int	elem_len;

	while (s[++(st->i)])
	{
		if (s[st->i] != c)
		{
			st->k = 0;
			set_quote(s[st->i], st);
			elem_len = count_elem_len(s, c, st->i, st->is_quote);
			arr[st->j] = (char *)malloc((elem_len + 1) * sizeof(char));
			if (!arr[st->j])
				return (free_arr(arr));
			while (s[st->i] && (s[st->i] != c || st->is_quote))
			{
				arr[st->j][st->k++] = s[st->i++];
				set_quote(s[st->i], st);
			}
			arr[st->j++][st->k] = '\0';
			// arr[st->j] = '\0';
			if (!s[st->i])
				return (arr);
		}
	}
	return (arr);
}

char	**ft_split_pipe(char const *s, char c)
{
	char	**arr;
	int		nb_elems;
	t_split	*st;

	if (!s)
		return (NULL);
	st = malloc(sizeof(t_split));
	init_struct(st);
	nb_elems = count_elems(s, c);
	arr = (char **)malloc((nb_elems + 1) * sizeof(char *));
	if (!arr)
	{
		free(st);
		return (NULL);
	}
	arr[nb_elems] = 0;
	arr = fill_arr(s, arr, c, st);
	free(st);
	return (arr);
}

// "a|b" | "b|c"