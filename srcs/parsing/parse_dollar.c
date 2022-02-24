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

void	replace_dollar(t_node *nodes, t_parsing *ps, t_shell *sh, int *pos_dollar)
{
	int		key_len;
	char	*tmp;
	char	*value;

	key_len = get_key_len(nodes[ps->i].cmd[ps->j], *pos_dollar + 1);
	tmp = str_slice(nodes[ps->i].cmd[ps->j], *pos_dollar + 1,
		*pos_dollar + key_len + 1);
	if (!tmp)
		ft_exit(sh, ps, nodes, "Fail to malloc key in replace dollar\n");
	value = get_env_var_value(sh->env, tmp);
	free(tmp);
	if (!value)
		ft_exit(sh, ps, nodes, "Fail to malloc value in replace dollar\n");
	tmp = ft_strdup(nodes[ps->i].cmd[ps->j]);
	if (!tmp)
	{
		free(value);
		ft_exit(sh, ps, nodes, "Fail to malloc tmp in replace dollar\n");
	}
	free(nodes[ps->i].cmd[ps->j]);
	nodes[ps->i].cmd[ps->j] = replace_in_str(tmp,
		value, *pos_dollar, key_len);
	ps->k = *pos_dollar + ft_strlen(value) - 1;
	free(value);
	if (!nodes[ps->i].cmd[ps->j])
		ft_exit(sh, ps, nodes, "Fail to malloc node cmd in replace dollar\n");
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
			while (pos_dollar > -1 && !ps->is_s_quote)
			{
				set_quotes_for_cmd(ps, nodes);
				replace_dollar(nodes, ps, sh, &pos_dollar);
				pos_dollar = get_next_dollar(nodes[ps->i].cmd[ps->j], ps->k);
			}
			printf("CMD : %s\n", nodes[ps->i].cmd[ps->j]);
		}
	}
}

// "$a$b"

// $ for infiles / outfiles


// static void	set_quotes_for_infiles(t_parsing *ps, t_node *n, int *k)
// {
// 	if (n[ps->i].infiles[*k] == '\'')
// 	{
// 		if (ps->is_s_quote)
// 			ps->is_s_quote = 0;
// 		else
// 			ps->is_s_quote = 1;
// 		(*k)++;
// 	}
// 	else if (n[ps->i].infiles[*k] == '"')
// 	{
// 		if (ps->is_d_quote)
// 			ps->is_d_quote = 0;
// 		else
// 			ps->is_d_quote = 1;
// 		(*k)++;
// 	}
// }

// static void	set_quotes_for_outfiles(t_parsing *ps, t_node *n, int *k)
// {
// 	if (n[ps->i].outfiles[*k] == '\'')
// 	{
// 		if (ps->is_s_quote)
// 			ps->is_s_quote = 0;
// 		else
// 			ps->is_s_quote = 1;
// 		(*k)++;
// 	}
// 	else if (n[ps->i].outfiles[*k] == '"')
// 	{
// 		if (ps->is_d_quote)
// 			ps->is_d_quote = 0;
// 		else
// 			ps->is_d_quote = 1;
// 		(*k)++;
// 	}
// }


		// k = 0;
		// set_quotes_for_infiles(ps, nodes, &k);
		// pos_dollar = get_next_dollar(nodes[ps->i].infiles, k);
		// while (pos_dollar > -1 && !ps->is_s_quote)
		// {
		// 	set_quotes_for_infiles(ps, nodes, &k);
		// 	key_len = get_key_len(nodes[ps->i].infiles, pos_dollar + 1);
		// 	key = str_slice(nodes[ps->i].infiles, pos_dollar + 1,
		// 		pos_dollar + key_len + 1);
		// 	value = get_env_var_value(sh->env, key);
		// 	free(key);
		// 	nodes[ps->i].infiles = replace_in_str(nodes[ps->i].infiles,
		// 		value, pos_dollar, key_len);
		// 	k += pos_dollar + ft_strlen(value);
		// 	pos_dollar = get_next_dollar(nodes[ps->i].infiles, k);
		// }
		// printf("INFILE : %s\n", nodes[ps->i].infiles);

		// k = 0;
		// set_quotes_for_outfiles(ps, nodes, &k);
		// pos_dollar = get_next_dollar(nodes[ps->i].outfiles, k);
		// while (pos_dollar > -1 && !ps->is_s_quote)
		// {
		// 	set_quotes_for_outfiles(ps, nodes, &k);
		// 	key_len = get_key_len(nodes[ps->i].outfiles, pos_dollar + 1);
		// 	key = str_slice(nodes[ps->i].outfiles, pos_dollar + 1,
		// 		pos_dollar + key_len + 1);
		// 	value = get_env_var_value(sh->env, key);
		// 	free(key);
		// 	nodes[ps->i].outfiles = replace_in_str(nodes[ps->i].outfiles,
		// 		value, pos_dollar, key_len);
		// 	k += pos_dollar + ft_strlen(value);
		// 	pos_dollar = get_next_dollar(nodes[ps->i].outfiles, k);
		// }
		// printf("OUTFILE : %s\n", nodes[ps->i].outfiles);