#include "../../includes/minishell.h"

// // static void	set_quotes_while_dollar(t_parsing *ps, int j)
// // {
// // 	// do not move j in this function !!
// // 	if (ps->nodes[ps->i][j] == '\'')
// // 	{
// // 		if (ps->is_s_quote)
// // 			ps->is_s_quote = 0;
// // 		else
// // 			ps->is_s_quote = 1;
// // 		j++;
// // 	}
// // 	else if (ps->nodes[ps->i][j] == '"')
// // 	{
// // 		printf("quote after %d\n", j);
// // 		if (ps->is_d_quote)
// // 			ps->is_d_quote = 0;
// // 		else
// // 			ps->is_d_quote = 1;
// // 		j++;
// // 	}
// // }

// static void	set_quotes_after_pos_start(t_parsing *ps, int *j)
// {
// 	if (ps->nodes[ps->i][*j] == '\'')
// 	{
// 		if (ps->is_s_quote)
// 			ps->is_s_quote = 0;
// 		else
// 			ps->is_s_quote = 1;
// 		(*j)++;
// 	}
// 	else if (ps->nodes[ps->i][*j] == '"')
// 	{
// 		printf("quote after %d\n", *j);
// 		if (ps->is_d_quote)
// 			ps->is_d_quote = 0;
// 		else
// 			ps->is_d_quote = 1;
// 		(*j)++;
// 	}
// }

// static void	set_quotes_before_pos_start(t_parsing *ps, int pos_start)
// {
// 	int	j;

// 	j = -1;
// 	while (ps->nodes[ps->i][++j] && j <= pos_start)
// 	{
// 		if (ps->nodes[ps->i][j] == '\'')
// 		{
// 			if (ps->is_s_quote)
// 				ps->is_s_quote = 0;
// 			else
// 				ps->is_s_quote = 1;
// 		}
// 		else if (ps->nodes[ps->i][j] == '"')
// 		{
// 			printf("quote before %d\n", j);
// 			if (ps->is_d_quote)
// 				ps->is_d_quote = 0;
// 			else
// 				ps->is_d_quote = 1;
// 		}
// 	}
// }

// void	expand_dollar_value(t_node *nodes, t_parsing *ps, t_shell *sh, int pos_start)
// {
// 	char	*key;
// 	char	*value;
// 	char	*cmd;
// 	char	*tmp;
// 	char	*before_dollar;
// 	int	j;

// 	cmd = NULL;
// 	set_quotes_before_pos_start(ps, pos_start);
// 	if (!ps->is_d_quote && !ps->is_s_quote)
// 		j = pos_start;
// 	else
// 		j = pos_start + 1;
// 	while (ps->nodes[ps->i][j])
// 	{
// 		set_quotes_after_pos_start(ps, &j);
// 		while (contains_dollar(ps, ps->nodes[ps->i], j) > -1 && !ps->is_s_quote)
// 		{
// 			if (ps->nodes[ps->i][j] == '$' && !is_space(ps->nodes[ps->i][j + 1]))
// 			{
// 				before_dollar = str_slice(ps->nodes[ps->i], pos_start, j);
// 				if (!before_dollar)
// 					ft_exit(sh, ps, nodes, "Fail to malloc before dollar in expand dollar\n");
// 				pos_start = j + 1;
// 				while (ps->nodes[ps->i][++j] && (ft_isalnum(ps->nodes[ps->i][j]) ||
// 					ps->nodes[ps->i][j] ==  '_'))
// 						continue ;
// 				key = str_slice(ps->nodes[ps->i], pos_start, j);
// 				if (!key)
// 					ft_exit(sh, ps, nodes, "Fail to malloc key in expand dollar\n");
// 				value = get_env_var_value(sh->env, key);
// 				if (!value)
// 					ft_exit(sh, ps, nodes, "Fail to malloc value in expand dollar\n");
// 				if (cmd)
// 				{
// 					tmp = ft_strjoin(cmd, before_dollar);
// 					if (!tmp)
// 						ft_exit(sh, ps, nodes, "Fail to malloc value in expand dollar\n");
// 					free(cmd);
// 					cmd = ft_strjoin(tmp, value);
// 					free(tmp);
// 				}
// 				else
// 				{
// 					cmd = ft_strjoin(before_dollar, value);
// 				}
// 				pos_start += ft_strlen(key);
// 				if (!cmd)
// 					ft_exit(sh, ps, nodes, "Fail to malloc cmd in expand dollar\n");
// 			}
// 			if (ps->nodes[ps->i][j] == '$' && !is_space(ps->nodes[ps->i][j + 1]))
// 				continue ;
// 			if (!ps->nodes[ps->i][j] || !ps->nodes[ps->i][j + 1]
// 				|| (is_space(ps->nodes[ps->i][j]) && !ps->is_d_quote)
// 				|| (ps->is_d_quote && ps->nodes[ps->i][j] == '"' && is_space(ps->nodes[ps->i][j + 1])))
// 			{
// 				printf("1st break at %d\n", j);
// 				break ;
// 			}
// 			j++;
// 		}
// 		if (!ps->nodes[ps->i][j] || !ps->nodes[ps->i][j + 1]
// 			|| (is_space(ps->nodes[ps->i][j]) && !ps->is_s_quote && !ps->is_d_quote)
// 			|| (ps->is_d_quote && ps->nodes[ps->i][j] == '"' && is_space(ps->nodes[ps->i][j + 1])))
// 		{
// 			printf("2nd break at %d\n", j);
// 			break ;
// 		}
// 		j++;
// 	}
// 	if (cmd)
// 	{
// 		pos_start = j;
// 		if (ps->is_d_quote)
// 		{
// 			while (ps->nodes[ps->i][j] && ps->nodes[ps->i][j] != '"')
// 				j++;
// 		}
// 		else
// 		{
// 			while (ps->nodes[ps->i][j] && (ps->nodes[ps->i][j] != ' ' && ps->nodes[ps->i][j] != '\t'))
// 				j++;
// 		}
// 		printf("%d %d\n", pos_start, j);
// 		value = str_slice(ps->nodes[ps->i], pos_start, j + 1);
// 		if (!value)
// 			ft_exit(sh, ps, nodes, "Fail to malloc value in expand dollar\n");
// 		cmd = ft_strjoin(cmd, value);
// 		if (!cmd)
// 			ft_exit(sh, ps, nodes, "Fail to malloc cmd in expand dollar\n");
// 		nodes[ps->i].cmd[ps->pos_cmd] = ft_strdup(cmd);
// 		if (!nodes[ps->i].cmd[ps->pos_cmd])
// 			ft_exit(sh, ps, nodes, "Fail to malloc node cmd in expand dollar\n");
// 		free(key);
// 		free(value);
// 		free(cmd);
// 		free(before_dollar);
// 	}
// 	else
// 	{
// 		nodes[ps->i].cmd[ps->pos_cmd] = str_slice(ps->nodes[ps->i], pos_start, j + 1);
// 		if (!nodes[ps->i].cmd[ps->pos_cmd])
// 			ft_exit(sh, ps, nodes, "Fail to malloc node cmd in expand dollar\n");
// 	}
// }

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

char	*ret_null_free(char *ret, char *s)
{
	if (s)
		free(s);
	return (ret);
}

char	*replace_in_str(char *s, char *value, int pos, int len)
{
	char	*aside_dollar;
	char	*tmp;

	aside_dollar = str_slice(s, 0, pos);
	if (!aside_dollar)
	{
		printf("1st aside dollar failed\n");
		return (NULL);
	}
	tmp = ft_strjoin(aside_dollar, value);
	if (!tmp)
		return (ret_null_free(NULL, aside_dollar));
	// printf("before : %s\n", tmp);
	// free(aside_dollar);
	
	// aside_dollar = str_slice(s, i, pos);
	// if (!aside_dollar)
	// 	return (ret_null_free(NULL, tmp));
	// // printf("after : %s\n", aside_dollar);
	// free(s);
	s = ft_strjoin(tmp, s + pos + len + 1);
	free(tmp);
	free(aside_dollar);
	return (s);
}

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
			pos_dollar = get_next_dollar(nodes[ps->i].cmd[ps->j], k);
			while (pos_dollar > -1)
			{
				key_len = get_key_len(nodes[ps->i].cmd[ps->j], pos_dollar + 1);
				key = str_slice(nodes[ps->i].cmd[ps->j], pos_dollar + 1,
					pos_dollar + key_len + 1);
				value = get_env_var_value(sh->env, key);
				free(key);
				nodes[ps->i].cmd[ps->j] = replace_in_str(nodes[ps->i].cmd[ps->j],
					value, pos_dollar, key_len);
				k += pos_dollar + ft_strlen(value);
				pos_dollar = get_next_dollar(nodes[ps->i].cmd[ps->j], k);
			}
			printf("CMD : %s\n", nodes[ps->i].cmd[ps->j]);
		}
	}
}