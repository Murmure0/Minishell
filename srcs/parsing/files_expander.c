/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_expander.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmasse <vmasse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 15:19:07 by vmasse            #+#    #+#             */
/*   Updated: 2022/02/25 19:30:06 by vmasse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	skip_spaces_local(t_parsing *ps, int *j)
{
	while (ps->nodes[ps->i][*j] && is_space(ps->nodes[ps->i][*j]))
	{
		if (ps->nodes[ps->i][*j + 1])
			(*j)++;
		else
			break ;
	}
}

void	set_quotes_for_files(t_parsing *ps, int *j)
{
	if (ps->nodes[ps->i][*j] == '\'')
	{
		if (ps->is_s_quote)
			ps->is_s_quote = 0;
		else
			ps->is_s_quote = 1;
		(*j)++;
	}
	else if (ps->nodes[ps->i][*j] == '"')
	{
		if (ps->is_d_quote)
			ps->is_d_quote = 0;
		else
			ps->is_d_quote = 1;
		(*j)++;
	}
}

void	replace_dollar_files(t_node *n, t_parsing *ps, t_shell *sh, int *pos)
{
	int		key_len;
	char	*tmp;
	char	*value;

	key_len = get_key_len(ps->nodes[ps->i], *pos + 1);
	tmp = str_slice(ps->nodes[ps->i], *pos + 1, *pos + key_len + 1);
	if (!tmp)
		ft_exit(sh, ps, n, "Fail to malloc key in replace dollar outfiles\n");
	value = get_env_var_value(sh->env, tmp);
	free(tmp);
	if (!value)
		ft_exit(sh, ps, n, "Fail to malloc value in replace dollar outfiles\n");
	tmp = ft_strdup(ps->nodes[ps->i]);
	if (!tmp)
	{
		free(value);
		ft_exit(sh, ps, n, "Fail to malloc tmp in replace dollar outfiles\n");
	}
	free(ps->nodes[ps->i]);
	ps->nodes[ps->i] = replace_in_str(tmp,
			value, *pos, key_len);
	ps->k = *pos + ft_strlen(value) - 1;
	free(value);
	if (!ps->nodes[ps->i])
		ft_exit(sh, ps, n, "Fail to malloc node cmd in replace dollar files\n");
}

void	quotes_and_dollar_files(t_node *nodes, t_parsing *ps, t_shell *sh)
{
	int	j;
	int	pos_dollar;

	j = ps->j + 1;
	skip_spaces_local(ps, &j);
	set_quotes_for_files(ps, &j);
	pos_dollar = get_next_dollar(ps->nodes[ps->i], j);
	while (pos_dollar > -1 && !ps->is_s_quote
		&& ft_isalnum(ps->nodes[ps->i][j + 1])
		&& !is_space(ps->nodes[ps->i][j]))
	{
		set_quotes_for_files(ps, &j);
		replace_dollar_files(nodes, ps, sh, &pos_dollar);
		pos_dollar = get_next_dollar(ps->nodes[ps->i], j);
	}
}
