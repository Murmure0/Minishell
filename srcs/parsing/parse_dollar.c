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

char	*replace_in_str(char *s, char *value, int pos, int len)
{
	char	*before_dollar;
	char	*tmp;

	before_dollar = str_slice(s, 0, pos);
	if (!before_dollar)
		return (NULL);
	tmp = ft_strjoin(before_dollar, value);
	if (!tmp)
	{
		free(before_dollar);
		return (NULL);
	}
	s = ft_strjoin(tmp, s + pos + len + 1);
	free(tmp);
	free(before_dollar);
	return (s);
}

static void	set_quotes_for_cmd(t_parsing *ps, t_node *n, int *k)
{
	if (n[ps->i].cmd[ps->j][*k] == '\'')
	{
		if (ps->is_s_quote)
			ps->is_s_quote = 0;
		else
			ps->is_s_quote = 1;
		(*k)++;
	}
	else if (n[ps->i].cmd[ps->j][*k] == '"')
	{
		if (ps->is_d_quote)
			ps->is_d_quote = 0;
		else
			ps->is_d_quote = 1;
		(*k)++;
	}
}

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

void	expand_dollar_value(t_node *nodes, t_parsing *ps, t_shell *sh)
{
	int		k;
	int		pos_dollar;
	char	*key;
	char	*value;
	int		key_len;

	ps->i = -1;
	while (++(ps->i) < ps->pipe_nb + 1)
	{
		ps->j = -1;
		// faire 3 fonctions => expand_cmd, expand_infiles et expand_outfiles
		while (nodes[ps->i].cmd[++(ps->j)])
		{
			k = 0;
			set_quotes_for_cmd(ps, nodes, &k);
			pos_dollar = get_next_dollar(nodes[ps->i].cmd[ps->j], k);
			while (pos_dollar > -1 && !ps->is_s_quote)
			{
				set_quotes_for_cmd(ps, nodes, &k);
				key_len = get_key_len(nodes[ps->i].cmd[ps->j], pos_dollar + 1);
				key = str_slice(nodes[ps->i].cmd[ps->j], pos_dollar + 1,
					pos_dollar + key_len + 1);
				value = get_env_var_value(sh->env, key);
				free(key);
				nodes[ps->i].cmd[ps->j] = replace_in_str(nodes[ps->i].cmd[ps->j],
					value, pos_dollar, key_len);
				k += pos_dollar + ft_strlen(value) - 1;
				printf("%d %s\n", k, nodes[ps->i].cmd[ps->j]);
				pos_dollar = get_next_dollar(nodes[ps->i].cmd[ps->j], k);
			}
			// printf("CMD : %s\n", nodes[ps->i].cmd[ps->j]);
		}

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
	}
}

// "$a$b"