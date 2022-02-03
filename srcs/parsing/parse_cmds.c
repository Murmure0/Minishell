#include "../../includes/minishell.h"

void	add_command_args(t_node *nodes, t_parsing *ps)
{
	int		pos_start;

	while (ps->nodes[ps->i][ps->j] && ps->nodes[ps->i][ps->j] != '<' && ps->nodes[ps->i][ps->j] != '>')
	{
		while (ps->nodes[ps->i] && ps->nodes[ps->i][ps->j] && (ps->nodes[ps->i][ps->j] == '\t' || ps->nodes[ps->i][ps->j] == ' '))
			ps->j++;
		pos_start = ps->j;
		while (ps->nodes[ps->i][ps->j] && ps->nodes[ps->i][ps->j] != '\t' && ps->nodes[ps->i][ps->j] != ' ' && ps->nodes[ps->i][ps->j] != '<' && ps->nodes[ps->i][ps->j] != '>')
			ps->j++;
		nodes[ps->i].cmd[ps->pos_cmd] = str_slice(ps->nodes[ps->i], pos_start, ps->j);
		if (!nodes[ps->i].cmd[ps->pos_cmd])
			return ;
		ps->j++;
		ps->pos_cmd++;
	}
	nodes[ps->i].cmd[ps->pos_cmd - 1] = 0;
}

void	add_command(t_node *nodes, t_parsing *ps)
{
	int		pos_start;

	while (ps->nodes[ps->i][ps->j] && (ps->nodes[ps->i][ps->j] == '\t' || ps->nodes[ps->i][ps->j] == ' '))
		ps->j++;
	pos_start = ps->j;
	nodes[ps->i].cmd = malloc(sizeof(char *) * (get_cmds_nb(ps->nodes[ps->i]) + 1));
	if (!nodes[ps->i].cmd)
		return ;
	while (ps->nodes[ps->i] && ps->nodes[ps->i][ps->j])
	{
		if (ps->nodes[ps->i][ps->j] == '\t' || ps->nodes[ps->i][ps->j] == ' ' || ps->nodes[ps->i][ps->j] == '<' || ps->nodes[ps->i][ps->j] == '>')
			break ;
		ps->j++;
	}
	nodes[ps->i].cmd[ps->pos_cmd] = str_slice(ps->nodes[ps->i], pos_start, ps->j);
	if (!nodes[ps->i].cmd[ps->pos_cmd++])
		return ;
	add_command_args(nodes, ps);
}