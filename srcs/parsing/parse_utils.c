/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 17:08:35 by vmasse            #+#    #+#             */
/*   Updated: 2022/03/09 14:18:00 by mberthet         ###   ########.fr       */
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

int	check_space_between_redirs(t_parsing *ps)
{
	int	j;

	j = ps->j;
	// if (ps->nodes[ps->i][j] && ps->nodes[ps->i][j + 1]
	// 	&& is_space(ps->nodes[ps->i][j + 1]))
	if (is_space(ps->nodes[ps->i][j]))
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

char	*replace_in_str(char *s, char *value, int pos, int len)
{
	char	*before_dollar;
	char	*tmp;
	char	*tmp_two;
	char	*ret;

	before_dollar = str_slice(s, 0, pos);
	if (!before_dollar)
		return (NULL);
	tmp = ft_strjoin(before_dollar, value);
	free(before_dollar);
	if (!tmp)
		return (NULL);
	tmp_two = ft_strdup(s);
	if (!tmp_two)
	{
		free(tmp);
		return (NULL);
	}
	ret = ft_strjoin(tmp, tmp_two + pos + len + 1);
	free(tmp);
	free(tmp_two);
	return (ret);
}
