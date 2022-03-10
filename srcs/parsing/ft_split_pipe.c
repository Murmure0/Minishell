/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmasse <vmasse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 16:29:40 by vmasse            #+#    #+#             */
/*   Updated: 2022/03/10 15:15:43 by vmasse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static	int	count_elem_len(char const *s, char c, t_split *st)
{
	int	len;
	int	tmp;
	int	i;

	len = 0;
	tmp = st->is_quote;
	i = st->i;
	while (s[i] && (s[i] != c || st->is_quote))
	{
		set_quote_utils(s[i], st);
		len++;
		i++;
	}
	st->is_quote = tmp;
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
			set_quote_utils(s[st->i], st);
			elem_len = count_elem_len(s, c, st);
			arr[st->j] = (char *)malloc((elem_len + 1) * sizeof(char));
			if (!arr[st->j])
				return (free_arr(arr));
			while (s[st->i] && (s[st->i] != c || st->is_quote))
			{
				arr[st->j][st->k++] = s[st->i++];
				set_quote_utils(s[st->i], st);
			}
			arr[st->j++][st->k] = '\0';
			if (!check_end(st, s, arr))
				return (arr);
		}
	}
	arr[st->j] = NULL;
	return (arr);
}

static	int	count_elems(char const *s, char c, t_split *st)
{
	int	i;
	int	nb_elems;

	nb_elems = 1;
	i = -1;
	st->is_quote = 0;
	while (s[++i])
	{
		set_quote_utils(s[i], st);
		if (s[i] == '\'' || s[i] == '"')
			continue ;
		else if (!st->is_quote && s[i] == c)
			nb_elems++;
	}
	st->is_quote = 0;
	return (nb_elems);
}

char	**ft_split_pipe(char const *s, char c, t_parsing *ps)
{
	char	**arr;
	t_split	*st;
	int		elem_nb;

	st = malloc(sizeof(t_split));
	if (!s || !st)
		return (NULL);
	init_struct(st);
	elem_nb = count_elems(s, c, st);
	arr = (char **)malloc((elem_nb + 1) * sizeof(char *));
	if (!arr)
	{
		free(st);
		return (NULL);
	}
	arr = fill_arr(s, arr, c, st);
	ps->pipe_nb = st->j - 1;
	free(st);
	return (arr);
}
