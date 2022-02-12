#include "../../includes/minishell.h"

int	contains_dollar(char *s)
{
	int	i;

	i = -1;
	while (s && s[++i])
	{
		if (s[i] == '$')
			return (i);
	}
	return (-1);
}

void	expand_dollar_value(t_node *nodes, t_parsing *ps, t_shell *sh, int pos_start)
{
	char	*key;
	char	*value;
	char	*cmd;
	char	*before_dollar;
	int	j;

	j = -1;
	cmd = NULL;
	while (ps->nodes[ps->i][++j] && j < pos_start)
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
			if (ps->is_d_quote)
				ps->is_d_quote = 0;
			else
				ps->is_d_quote = 1;
		}
	}
	j = pos_start - 1;
	if (ps->is_s_quote || ps->is_d_quote)
		j++;
	while (ps->nodes[ps->i][++j])
	{
		if (ps->nodes[ps->i][j] == '\'')
		{
			printf("s quote after %d\n", j);
			if (ps->is_s_quote)
				ps->is_s_quote = 0;
			else
				ps->is_s_quote = 1;
			j++;
		}
		else if (ps->nodes[ps->i][j] == '"')
		{
			printf("d quote after %d\n", j);
			if (ps->is_d_quote)
				ps->is_d_quote = 0;
			else
				ps->is_d_quote = 1;
			j++;
		}
		if (ps->nodes[ps->i][j] == '$' && ps->nodes[ps->i][j + 1] && !ps->is_s_quote)
		{
			before_dollar = str_slice(ps->nodes[ps->i], pos_start, j);
			if (!before_dollar)
				ft_exit(sh, ps, nodes, "Fail to malloc cmd in expand dollar\n");
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
			cmd = ft_strjoin(before_dollar, value);
			if (!cmd)
				ft_exit(sh, ps, nodes, "Fail to malloc cmd in expand dollar\n");
			break ;
		}
		if (!ps->nodes[ps->i][j] || (is_space(ps->nodes[ps->i][j]) && !ps->is_s_quote && !ps->is_d_quote))
		{
			printf("break %d\n", j);
			break ;
		}
	}
	if (cmd)
	{
		pos_start = j;
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
		value = str_slice(ps->nodes[ps->i], pos_start, j + 1);
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
	printf("%s\n", nodes[ps->i].cmd[ps->pos_cmd]);
}