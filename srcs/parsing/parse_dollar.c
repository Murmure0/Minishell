/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dollar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmasse <vmasse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 19:31:57 by vmasse            #+#    #+#             */
/*   Updated: 2022/02/27 10:51:38 by vmasse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_key_len(char *s, int pos)
{
	int	len;

	len = 0;
	while (s[pos] && (ft_isalnum(s[pos]) || s[pos] == '_'))
	{
		len++;
		pos++;
	}
	return (len);
}

int	get_next_dollar(char *s, int pos)
{
	while (s && s[pos])
	{
		if (s[pos] == '$')
			return (pos);
		pos++;
	}
	return (-1);
}

void	set_quotes_for_cmd(t_parsing *ps, t_node *n)
{
	if (n[ps->i].cmd[ps->j][ps->k] == '\'')
	{
		if (ps->is_s_quote)
			ps->is_s_quote = 0;
		else
			ps->is_s_quote = 1;
		ps->k++;
	}
	else if (n[ps->i].cmd[ps->j][ps->k] == '"')
	{
		if (ps->is_d_quote)
			ps->is_d_quote = 0;
		else
			ps->is_d_quote = 1;
		ps->k++;
	}
}

void	replace_dollar(t_node *n, t_parsing *ps, t_shell *sh, int *pos)
{
	int		key_len;
	char	*tmp;
	char	*value;

	key_len = get_key_len(n[ps->i].cmd[ps->j], *pos + 1);
	tmp = str_slice(n[ps->i].cmd[ps->j], *pos + 1, *pos + key_len + 1);
	if (!tmp)
		ft_exit(sh, ps, n, "Fail to malloc key in replace dollar\n");
	value = get_env_var_value(sh->env, tmp);
	free(tmp);
	if (!value)
		ft_exit(sh, ps, n, "Fail to malloc value in replace dollar\n");
	tmp = ft_strdup(n[ps->i].cmd[ps->j]);
	if (!tmp)
	{
		free(value);
		ft_exit(sh, ps, n, "Fail to malloc tmp in replace dollar\n");
	}
	free(n[ps->i].cmd[ps->j]);
	n[ps->i].cmd[ps->j] = replace_in_str(tmp, value, *pos, key_len);
	if (ft_strcmp(value, ""))
		ps->k = *pos + ft_strlen(value) - 1;
	free_value_tmp(value, tmp);
	if (!n[ps->i].cmd[ps->j])
		ft_exit(sh, ps, n, "Fail to malloc node cmd in replace dollar\n");
}

void	expand_dollar_value_cmd(t_node *nodes, t_parsing *ps, t_shell *sh)
{
	int		pos_dollar;

	ps->i = -1;
	while (++(ps->i) < ps->pipe_nb + 1)
	{
		ps->j = -1;
		while (nodes[ps->i].cmd[++(ps->j)])
		{
			ps->k = 0;
			set_quotes_for_cmd(ps, nodes);
			pos_dollar = get_next_dollar(nodes[ps->i].cmd[ps->j], ps->k);
			while (pos_dollar > -1 && !ps->is_s_quote
				&& (ft_isalnum(nodes[ps->i].cmd[ps->j][pos_dollar + 1])
				|| nodes[ps->i].cmd[ps->j][pos_dollar + 1] == '_'))
			{
				set_quotes_for_cmd(ps, nodes);
				replace_dollar(nodes, ps, sh, &pos_dollar);
				pos_dollar = get_next_dollar(nodes[ps->i].cmd[ps->j], ps->k);
			}
		}
	}
}
