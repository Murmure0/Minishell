#include "../../includes/minishell.h"

// char	*get_file_name(t_parsing *ps)
// {
// 	int		pos_start;

// 	ps->j++;
// 	while (ps->nodes[ps->i] && ps->nodes[ps->i][ps->j] && (ps->nodes[ps->i][ps->j] == '\t' || ps->nodes[ps->i][ps->j] == ' '))
// 		ps->j++;
// 	pos_start = ps->j;
// 	while (ps->nodes[ps->i] && ps->nodes[ps->i][ps->j])
// 	{
// 		if (ps->nodes[ps->i][ps->j] == '\t' || ps->nodes[ps->i][ps->j] == ' ' || ps->nodes[ps->i][ps->j] == '<' || ps->nodes[ps->i][ps->j] == '>')
// 			break ;
// 		ps->j++;
// 	}
// 	return (str_slice(ps->nodes[ps->i], pos_start, ps->j));
// }

// void	add_command_args(t_node *nodes, t_parsing *ps)
// {
// 	int		pos_start;

// 	while (ps->nodes[ps->i][ps->j] && ps->nodes[ps->i][ps->j] != '<' && ps->nodes[ps->i][ps->j] != '>')
// 	{
// 		while (ps->nodes[ps->i] && ps->nodes[ps->i][ps->j] && (ps->nodes[ps->i][ps->j] == '\t' || ps->nodes[ps->i][ps->j] == ' '))
// 			ps->j++;
// 		pos_start = ps->j;
// 		while (ps->nodes[ps->i][ps->j] && ps->nodes[ps->i][ps->j] != '\t' && ps->nodes[ps->i][ps->j] != ' ' && ps->nodes[ps->i][ps->j] != '<' && ps->nodes[ps->i][ps->j] != '>')
// 			ps->j++;
// 		nodes[ps->i].cmd[ps->pos_cmd] = str_slice(ps->nodes[ps->i], pos_start, ps->j);
// 		if (!nodes[ps->i].cmd[ps->pos_cmd])
// 			return ;
// 		ps->j++;
// 		ps->pos_cmd++;
// 	}
// 	nodes[ps->i].cmd[ps->pos_cmd - 1] = 0;
// }

// void	add_command(t_node *nodes, t_parsing *ps)
// {
// 	int		pos_start;

// 	while (ps->nodes[ps->i][ps->j] && (ps->nodes[ps->i][ps->j] == '\t' || ps->nodes[ps->i][ps->j] == ' '))
// 		ps->j++;
// 	pos_start = ps->j;
// 	nodes[ps->i].cmd = malloc(sizeof(char *) * (get_cmds_nb(ps->nodes[ps->i]) + 1));
// 	if (!nodes[ps->i].cmd)
// 		return ;
// 	while (ps->nodes[ps->i] && ps->nodes[ps->i][ps->j])
// 	{
// 		if (ps->nodes[ps->i][ps->j] == '\t' || ps->nodes[ps->i][ps->j] == ' ' || ps->nodes[ps->i][ps->j] == '<' || ps->nodes[ps->i][ps->j] == '>')
// 			break ;
// 		ps->j++;
// 	}
// 	nodes[ps->i].cmd[ps->pos_cmd] = str_slice(ps->nodes[ps->i], pos_start, ps->j);
// 	if (!nodes[ps->i].cmd[ps->pos_cmd++])
// 		return ;
// 	add_command_args(nodes, ps);
// }

// void	add_file(t_node *nodes, t_parsing *ps, int redir)
// {
// 	if (redir == 1)
// 	{
// 		nodes[ps->i].infiles[ps->pos_infiles].redir = redir;
// 		nodes[ps->i].infiles[ps->pos_infiles].name = get_file_name(ps);
// 		nodes[ps->i].infiles[ps->pos_infiles].pos = ps->j;
// 		ps->pos_infiles++;
// 	}
// 	else if (redir == 2 || redir == 3)
// 	{
// 		nodes[ps->i].outfiles[ps->pos_outfiles].redir = redir;
// 		nodes[ps->i].outfiles[ps->pos_outfiles].name = get_file_name(ps);
// 		nodes[ps->i].outfiles[ps->pos_outfiles].pos = ps->j;
// 		ps->pos_outfiles++;
// 	}
// 	add_command(nodes, ps);
// }

// t_node	*parse(t_node *nodes, t_parsing *ps)
// {
// 	if (!check_quotes_for_pipe_split(ps))
// 		return (NULL);
// 	ps->nodes = ft_split(ps->prompt, '|');
// 	if (!ps->nodes)
// 		return (NULL);
// 	ps->pipe_nb = arr_len(ps->nodes) - 1;
// 	nodes = malloc(sizeof(t_node) * (ps->pipe_nb + 1));
// 	if (!nodes)
// 		return (NULL);
// 	ps->i = -1;
// 	while(ps->nodes[++(ps->i)])
// 	{
// 		ps->pos_infiles = 0;
// 		ps->pos_outfiles = 0;
// 		ps->pos_cmd = 0;
// 		nodes[ps->i].infiles = malloc(sizeof(t_token) * get_files_nb(ps->nodes[ps->i], '<'));
// 		if (!nodes[ps->i].infiles)
// 			return (NULL);
// 		nodes[ps->i].outfiles = malloc(sizeof(t_token) * get_files_nb(ps->nodes[ps->i], '>'));
// 		if (!nodes[ps->i].outfiles)
// 			return (NULL);
// 		ps->j = 0;
// 		while (ps->nodes[ps->i][ps->j])
// 		{
// 			while (ps->nodes[ps->i][ps->j] && (ps->nodes[ps->i][ps->j] == '\t' || ps->nodes[ps->i][ps->j] == ' '))
// 				ps->j++;
// 			if (ps->nodes[ps->i][ps->j] == '<')
// 			{
// 				if (ps->nodes[ps->i][ps->j + 1] && ps->nodes[ps->i][ps->j + 1] == '<')
// 				{
// 					printf("add heredoc\n");
// 					ps->j++;
// 				}
// 				else if (ps->nodes[ps->i][ps->j + 1])
// 				{
// 					printf("add infile name\n");
// 					add_file(nodes, ps, 1);
// 				}
// 				else
// 					return (NULL); // erreur -> no infile
// 			}
// 			else if (ps->nodes[ps->i][ps->j] == '>')
// 			{
// 				if (ps->nodes[ps->i][ps->j + 1] && ps->nodes[ps->i][ps->j + 1] == '>')
// 				{
// 					printf("add outfile + append\n");
// 					ps->j++;
// 					add_file(nodes, ps, 3);
// 				}
// 				else if (ps->nodes[ps->i][ps->j + 1])
// 				{
// 					add_file(nodes, ps, 2);
// 					printf("add outfile name\n");
// 				}
// 				else
// 					return (NULL); // erreur -> no outfile
// 			}
// 			else
// 			{
// 				// add_command(nodes, ps);
// 			}
// 			if (ps->nodes[ps->i][ps->j])
// 				ps->j++;
// 		}
// 	}
// 	return (nodes);
// }

int	init_global_struct(t_node *nodes, t_parsing *ps)
{
	if (!check_quotes_for_pipe_split(ps))
		return (0);
	ps->nodes = ft_split(ps->prompt, '|');
	if (!ps->nodes)
		return (0);
	ps->pipe_nb = arr_len(ps->nodes) - 1;
	nodes = malloc(sizeof(t_node) * (ps->pipe_nb + 1));
	if (!nodes)
		return (0);
	ps->i = 0;
	return (1);
}

int	init_local_struct(t_node *nodes, t_parsing *ps)
{
	ps->pos_infiles = 0;
	ps->pos_outfiles = 0;
	ps->pos_cmd = 0;
	nodes[ps->i].infiles = malloc(sizeof(t_token) * get_files_nb(ps->nodes[ps->i], '<'));
	if (!nodes[ps->i].infiles)
		return (0);
	nodes[ps->i].outfiles = malloc(sizeof(t_token) * get_files_nb(ps->nodes[ps->i], '>'));
	if (!nodes[ps->i].outfiles)
		return (0);
	ps->j = 0;
	return (1);
}

int	process_parse(t_node *nodes, t_parsing *ps)
{
	while (ps->nodes[ps->i][ps->j] && (ps->nodes[ps->i][ps->j] == '\t' || ps->nodes[ps->i][ps->j] == ' '))
		ps->j++;
	if (ps->nodes[ps->i][ps->j] == '<')
	{
		if (ps->nodes[ps->i][ps->j + 1] && ps->nodes[ps->i][ps->j + 1] == '<')
		{
			printf("add heredoc\n");
			ps->j++;
		}
		else if (ps->nodes[ps->i][ps->j + 1])
		{
			printf("add infile name\n");
			add_file(nodes, ps, 1);
		}
		else
			return (NULL); // erreur -> no infile
	}
	else if (ps->nodes[ps->i][ps->j] == '>')
	{
		if (ps->nodes[ps->i][ps->j + 1] && ps->nodes[ps->i][ps->j + 1] == '>')
		{
			printf("add outfile + append\n");
			ps->j++;
			add_file(nodes, ps, 3);
		}
		else if (ps->nodes[ps->i][ps->j + 1])
		{
			add_file(nodes, ps, 2);
			printf("add outfile name\n");
		}
		else
			return (NULL); // erreur -> no outfile
	}
	else
	{
		// add_command(nodes, ps);
	}
}

t_node	*parse(t_node *nodes, t_parsing *ps)
{	
	if (!init_global_struct(nodes, ps))
		return (NULL);
	while(ps->nodes[ps->i])
	{
		if (!init_local_struct(nodes, ps))
			return (NULL);
		while (ps->nodes[ps->i][ps->j])
		{
			if (!process_parse(nodes, ps))
				return (NULL);
			ps->j++;
		}
		ps->i++;
	}
	return (nodes);
}
