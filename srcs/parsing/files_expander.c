/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_expander.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 15:19:07 by vmasse            #+#    #+#             */
/*   Updated: 2022/03/10 09:42:15 by mberthet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_exit_st;

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
	if (ps->nodes[ps->i][*j] == '\'' && !ps->is_d_quote)
	{
		if (ps->is_s_quote)
			ps->is_s_quote = 0;
		else
			ps->is_s_quote = 1;
	}
	else if (ps->nodes[ps->i][*j] == '"' && !ps->is_s_quote)
	{
		if (ps->is_d_quote)
			ps->is_d_quote = 0;
		else
			ps->is_d_quote = 1;
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

void	replace_exit_st_files(t_node *n, t_parsing *ps, t_shell *sh, int *pos)
{
	char	*status;
	char	*tmp;

	status = ft_itoa(g_exit_st);
	if (!status)
		ft_exit(sh, ps, n, "Fail to malloc status in replace dollar exit st");
	tmp = ft_strdup(ps->nodes[ps->i]);
	free(ps->nodes[ps->i]);
	if (!tmp)
	{
		free(status);
		ft_exit(sh, ps, n, "Fail to malloc tmp in replace dollar exit st");
	}
	ps->nodes[ps->i] = replace_in_str(tmp, status, *pos, 1);
	free(tmp);
	free(status);
	if (!ps->nodes[ps->i])
		ft_exit(sh, ps, n, "Fail to malloc nodes in replace dollar exit st");
}

void	quotes_and_dollar_files(t_node *nodes, t_parsing *ps, t_shell *sh)
{

	int	j;
	// int	pos_dollar;


	if (ps->nodes[ps->i][ps->j] == '>')
		j = ps->j + 1;
	else
		j = ps->j;
	
	skip_spaces_local(ps, &j);
	printf("0 contenu j : %c\n", ps->nodes[ps->i][j]);
	printf("1 contenu j : %c\n", ps->nodes[ps->i][j]);
	// pos_dollar = get_next_dollar(ps->nodes[ps->i], j);
	while (ps->nodes[ps->i][j]/*pos_dollar > -1 && !ps->is_s_quote &&*/ /*!is_space(ps->nodes[ps->i][j])*/ /*&& (ft_isalnum(ps->nodes[ps->i][j + 1])
			|| ps->nodes[ps->i][j + 1] == '_' || ps->nodes[ps->i][j + 1] == '?'*/)
	{
		set_quotes_for_files(ps, &j);
		if (ps->nodes[ps->i][j] == '$' && ps->nodes[ps->i][j + 1] == '?')
			replace_exit_st_files(nodes, ps, sh, &j);
		else if (ps->nodes[ps->i][j] == '$' && !ps->is_s_quote)
			replace_dollar_files(nodes, ps, sh, &j);
		// pos_dollar = get_next_dollar(ps->nodes[ps->i], j);
		printf("2 contenu j : %c\n", ps->nodes[ps->i][j]);
		j++;
	}
	ps->is_d_quote = 0;
	ps->is_s_quote = 0;
	printf("3 contenu j : %s\n", ps->nodes[ps->i]);
	// remove_quotes_files(ps);
	printf("4 contenu j : %s\n", ps->nodes[ps->i]);
}
