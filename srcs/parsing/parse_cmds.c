#include "../../includes/minishell.h"

int	process_get_cmds_nb(char *node, int i, int *nb)
{
	if (node[i] != ' ' && node[i] != '\t' && node[i] != '<' && node[i] != '>')
	{
		while (node[i] && (node[i] != ' ' && node[i] != '\t'))
			i++;
		(*nb)++;
	}
	else if (node[i] == '<' || node[i] == '>')
	{
		if (node[i + 1] && (node[i + 1] == ' ' || node[i + 1] == '\t'))
		{
			i++;
			while (node[i] && (node[i] == '\t' || node[i] == ' '))
				if (node[i + 1])
					i++;
		}
		while (node[i] && (node[i] != ' ' && node[i] != '\t'))
			i++;
	}
	return (i);
}

int	get_cmds_nb(char *node)
{
	int	i;
	int nb;

	i = 0;
	nb = 0;
	while (node && node[i])
	{
		i = process_get_cmds_nb(node, i, &nb);
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
		while (ps->nodes[ps->i][ps->j] && (ps->nodes[ps->i][ps->j] == '\t' || ps->nodes[ps->i][ps->j] == ' '))
			ps->j++;
		pos_start = ps->j;
		if (!ps->nodes[ps->i][ps->j])
			return ;
		while (ps->nodes[ps->i][ps->j] && ps->nodes[ps->i][ps->j] != '\t' && ps->nodes[ps->i][ps->j] != ' ')
		{
			if (ps->nodes[ps->i][ps->j] == '<' || ps->nodes[ps->i][ps->j] == '>')
			{
				stop = 1;
				break ;
			}
			ps->j++;
		}
		(*nodes[ps->i]).cmd[ps->pos_cmd] = str_slice(ps->nodes[ps->i], pos_start, ps->j);
		if (!(*nodes[ps->i]).cmd[ps->pos_cmd] || stop)
			return ;
		if (ps->nodes[ps->i][ps->j] && ps->nodes[ps->i][ps->j + 1])
			ps->j++;
		else
			break ;
		ps->pos_cmd++;
	}
	(*nodes[ps->i]).cmd[get_cmds_nb(ps->nodes[ps->i])] = 0;
}

void	add_command(t_node **nodes, t_parsing *ps)
{
	int		pos_start;

	while (ps->nodes[ps->i][ps->j] && (ps->nodes[ps->i][ps->j] == '\t' || ps->nodes[ps->i][ps->j] == ' '))
		ps->j++;
	pos_start = ps->j;
	(*nodes[ps->i]).cmd = malloc(sizeof(char *) * (get_cmds_nb(ps->nodes[ps->i]) + 1));
	if (!(*nodes[ps->i]).cmd)
		return ;
	while (ps->nodes[ps->i] && ps->nodes[ps->i][ps->j])
	{
		if (ps->nodes[ps->i][ps->j] == '\t' || ps->nodes[ps->i][ps->j] == ' ' || ps->nodes[ps->i][ps->j] == '<' || ps->nodes[ps->i][ps->j] == '>')
			break ;
		ps->j++;
	}
	(*nodes[ps->i]).cmd[ps->pos_cmd] = str_slice(ps->nodes[ps->i], pos_start, ps->j);
	if (!(*nodes[ps->i]).cmd[ps->pos_cmd])
		return ;
	ps->pos_cmd++;
	add_command_args(nodes, ps);
}
