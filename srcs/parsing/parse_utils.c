/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmasse <vmasse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 17:08:35 by vmasse            #+#    #+#             */
/*   Updated: 2022/02/23 14:51:21 by vmasse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	arr_len(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
	{
		i++;
	}
	return (i);
}

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

int	check_space_between_redirs(t_parsing *ps)
{
	int	j;

	j = ps->j;
	if (ps->nodes[ps->i][j] && ps->nodes[ps->i][j + 1]
		&& is_space(ps->nodes[ps->i][j + 1]))
	{
		j++;
		while (ps->nodes[ps->i][j] && is_space(ps->nodes[ps->i][j]))
		{
			if (ps->nodes[ps->i][j + 1])
				j++;
			else
				break ;
		}
		if (ps->nodes[ps->i][j] && is_chevron(ps->nodes[ps->i][j]))
		{
			printf("minishell: syntax error near unexpected token `%c'\n",
				ps->nodes[ps->i][j]);
			return (0);
		}
	}
	return (1);
}

void	skip_spaces(t_parsing *ps)
{
	while (ps->nodes[ps->i][ps->j] && is_space(ps->nodes[ps->i][ps->j]))
	{
		if (ps->nodes[ps->i][ps->j + 1])
			ps->j++;
		else
			break ;
	}
}

t_node	*parse_ret_free(t_node *nodes)
{
	free(nodes);
	return (NULL);
}