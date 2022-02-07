#include "../../includes/minishell.h"

int	get_cmds_nb(char *node)
{
	int	i;
	int nb;

	i = 0;
	nb = 0;
	while (node && node[i])
	{
		if (node[i] != ' ' && node[i] != '\t' && node[i] != '<' && node[i] != '>')
		{
			while (node[i] && (node[i] != ' ' && node[i] != '\t'))
				i++;
			nb++;
		}
		else if (node[i] == '<' || node[i] == '>')
		{
			if (node[i + 1] == '<' || node[i + 1] == '>')
			{
				i = i + 2;
				while (node[i] && is_space(node[i]))
					if (node[i + 1])
						i++;
				while (node[i] && node[i] != ' ' && node[i] != '\t' && node[i] != '<' && node[i] != '>')
					i++;
			}
			if (node[i] && node[i + 1] && is_space(node[i + 1]))
			{
				i++;
				while (node[i] && is_space(node[i]))
					if (node[i + 1])
						i++;
			}
			while (node[i] && (node[i] != ' ' && node[i] != '\t'))
				i++;
		}
		if (node[i] && node[i + 1])
			i++;
		else
			break ;
	}
	return (nb);
}

void	add_command_args(t_node **nodes, t_parsing *ps)
{
	int		pos_start;
	int		stop;

	stop = 0;
	while (ps->nodes[ps->i][ps->j] && ps->nodes[ps->i][ps->j] != '<' && ps->nodes[ps->i][ps->j] != '>')
	{
		skip_spaces(ps);
		pos_start = ps->j;
		if (!ps->nodes[ps->i][ps->j])
			return ;
		while (ps->nodes[ps->i][ps->j] && ps->nodes[ps->i][ps->j] != '\t' && ps->nodes[ps->i][ps->j] != ' ')
		{
			printf("|%c| pos : %d\n", ps->nodes[ps->i][ps->j], ps->j);
			if (is_chevron(ps->nodes[ps->i][ps->j]))
			{
				stop = 1;
				break ;
			}
			ps->j++;
		}
		if (stop)
		{
			(*nodes)[ps->i].cmd[ps->cmd_nb] = 0;
			return ; // faire + de tests
		}
		(*nodes)[ps->i].cmd[ps->pos_cmd] = str_slice(ps->nodes[ps->i], pos_start, ps->j);
		if (!(*nodes)[ps->i].cmd[ps->pos_cmd])
			return ;
		if (ps->nodes[ps->i][ps->j] && ps->nodes[ps->i][ps->j + 1])
			ps->j++;
		else
			break ;
		ps->pos_cmd++;
	}
	(*nodes)[ps->i].cmd[ps->cmd_nb] = 0;
}

void	add_command(t_node **nodes, t_parsing *ps)
{
	int		pos_start;

	skip_spaces(ps);
	pos_start = ps->j;
	while (ps->nodes[ps->i][ps->j])
	{
		if (is_space(ps->nodes[ps->i][ps->j]) || is_chevron(ps->nodes[ps->i][ps->j]))
			break ;
		ps->j++;
	}		
	(*nodes)[ps->i].cmd[ps->pos_cmd] = str_slice(ps->nodes[ps->i], pos_start, ps->j);
	if (!(*nodes)[ps->i].cmd[ps->pos_cmd])
		return ;
	ps->pos_cmd++;
	add_command_args(nodes, ps);
}
