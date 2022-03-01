/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 16:29:40 by vmasse            #+#    #+#             */
/*   Updated: 2022/03/01 13:43:17 by mberthet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
			if (!s[st->i])
			{
				arr[st->j] = NULL;
				return (arr);
			}
		}
	}
	arr[st->j] = NULL;
	return (arr);
}

char	**ft_split_pipe(char const *s, char c, t_parsing *ps)
{
	char	**arr;
	t_split	*st;

	if (!s)
		return (NULL);
	st = malloc(sizeof(t_split));
	if (!st)
		return (NULL);
	init_struct(st);
	arr = (char **)malloc((100) * sizeof(char *));
	if (!arr)
	{
		free(st);
		return (NULL);
	}
	arr = fill_arr(s, arr, c, st);
	ps->pipe_nb = st->j - 1;
	if (ps->pipe_nb == -1)
		ps->pipe_nb++;
	free(st);
	return (arr);
}