#include "../../includes/minishell.h"

int	contains_dollar(char *s, int pos)
{
	while (s && s[pos])
	{
		if (s[pos] == '$')
			return (pos);
		pos++;
	}
	return (-1);
}

static void	set_quotes_after_pos_start(t_parsing *ps, int *j)
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
		printf("quote after %d\n", *j);
		if (ps->is_d_quote)
			ps->is_d_quote = 0;
		else
			ps->is_d_quote = 1;
		(*j)++;
	}
}

static void	set_quotes_before_pos_start(t_parsing *ps, int pos_start)
{
	int	j;

	j = -1;
	while (ps->nodes[ps->i][++j] && j <= pos_start)
	{
		if (ps->nodes[ps->i][j] == '\'')
		{
			if (ps->is_s_quote)
				ps->is_s_quote = 0;
			else
				ps->is_s_quote = 1;
		}
		else if (ps->nodes[ps->i][j] == '"')
		{
			printf("quote before %d\n", j);
			if (ps->is_d_quote)
				ps->is_d_quote = 0;
			else
				ps->is_d_quote = 1;
		}
	}
}

void	expand_dollar_value(t_node *nodes, t_parsing *ps, t_shell *sh, int pos_start)
{
	char	*key;
	char	*value;
	char	*cmd;
	char	*tmp;
	char	*before_dollar;
	int	j;

	cmd = NULL;
	set_quotes_before_pos_start(ps, pos_start);
	if (!ps->is_s_quote && !ps->is_d_quote)
		j = pos_start - 1;
	else
		j = pos_start;
	while (ps->nodes[ps->i][++j])
	{
		set_quotes_after_pos_start(ps, &j);
		while (contains_dollar(ps->nodes[ps->i], j) > -1)
		{
			printf("%d\n", j);
			if (ps->nodes[ps->i][j] == '$' && !ps->is_s_quote)
			{
				before_dollar = str_slice(ps->nodes[ps->i], pos_start, j);
				if (!before_dollar)
					ft_exit(sh, ps, nodes, "Fail to malloc before dollar in expand dollar\n");
				pos_start = j + 1;
				while (ps->nodes[ps->i][++j] && (ft_isalnum(ps->nodes[ps->i][j]) ||
					ps->nodes[ps->i][j] ==  '_'))
						continue ;
				key = str_slice(ps->nodes[ps->i], pos_start, j);
				if (!key)
					ft_exit(sh, ps, nodes, "Fail to malloc key in expand dollar\n");
				value = get_env_var_value(sh->env, key);
				if (!value)
					ft_exit(sh, ps, nodes, "Fail to malloc value in expand dollar\n");
				if (cmd)
				{
					tmp = ft_strjoin(cmd, before_dollar);
					if (!tmp)
						ft_exit(sh, ps, nodes, "Fail to malloc tmp in expand dollar\n");
					free(cmd);
					cmd = ft_strjoin(tmp, value);
					free(tmp);
				}
				else
					cmd = ft_strjoin(before_dollar, value);
				if (!cmd)
					ft_exit(sh, ps, nodes, "Fail to malloc cmd in expand dollar\n");
				pos_start += ft_strlen(key);
			}
			if (ps->nodes[ps->i][j] == '$' && !ps->is_s_quote)
				continue ;
			if (!ps->nodes[ps->i][++j] || (is_space(ps->nodes[ps->i][j]) && !ps->is_d_quote))
				break ;
		}
		if (!ps->nodes[ps->i][j] || (is_space(ps->nodes[ps->i][j]) && !ps->is_s_quote && !ps->is_d_quote))
			break ;
	}
	if (cmd)
	{
		if (ps->is_d_quote)
		{
			while (ps->nodes[ps->i][++j] && ps->nodes[ps->i][j] != '"')
				continue ;
		}
		else
		{
			while (ps->nodes[ps->i][++j] && (ps->nodes[ps->i][j] != ' ' && ps->nodes[ps->i][j] != '\t'))
				continue ;
		}
		value = str_slice(ps->nodes[ps->i], pos_start, j);
		if (!value)
			ft_exit(sh, ps, nodes, "Fail to malloc value in expand dollar\n");
		cmd = ft_strjoin(cmd, value);
		if (!cmd)
			ft_exit(sh, ps, nodes, "Fail to malloc cmd in expand dollar\n");
		nodes[ps->i].cmd[ps->pos_cmd] = ft_strdup(cmd);
		if (!nodes[ps->i].cmd[ps->pos_cmd])
			ft_exit(sh, ps, nodes, "Fail to malloc node cmd in expand dollar\n");
		free(key);
		free(value);
		free(cmd);
		free(before_dollar);
	}
	else
	{
		nodes[ps->i].cmd[ps->pos_cmd] = str_slice(ps->nodes[ps->i], pos_start, j);
		if (!nodes[ps->i].cmd[ps->pos_cmd])
			ft_exit(sh, ps, nodes, "Fail to malloc node cmd in expand dollar\n");

	}
}

// "$USER HELLO $USER"
// "hello $USER how  are you $a $b"