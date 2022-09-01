/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_process_child_fd.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 13:31:26 by mberthet          #+#    #+#             */
/*   Updated: 2022/03/02 16:37:28 by mberthet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_exit_st;

int	find_fd_in(t_node *first_node)
{
	int	fd_in;

	fd_in = 0;
	if (first_node[0].infiles && first_node->in_id == 2)
	{
		fd_in = open(first_node[0].infiles, O_RDONLY);
		if (fd_in < 0)
		{
			g_exit_st = 1;
			write(2, first_node[0].infiles, ft_strlen(first_node[0].infiles));
			perror(": ");
		}
	}
	else if (first_node->in_id == 1 && !first_node->invalid_infile)
		fd_in = first_node->infile_hd;
	return (fd_in);
}

static int	pipe_case(t_exec *exec_st)
{
	int	pfd[2];

	if (pipe(pfd) < 0)
	{
		g_exit_st = -1;
		perror(": ");
		exit (g_exit_st);
	}
	exec_st->pfd_out = pfd[1];
	exec_st->pfd_in = pfd[0];
	exec_st->num_cmd++;
	return (0);
}

int	find_fd_out(t_node *first_node, t_exec *exec_st)
{
	int	fd_out;

	fd_out = 1;
	if (first_node[0].node_nb > 1)
		if (pipe_case(exec_st) < 0)
			return (g_exit_st);
	if (first_node[0].node_nb > 1 && !first_node[0].outfiles)
		fd_out = exec_st->pfd_out;
	else if (first_node[0].outfiles)
	{
		if (first_node[0].append == 2)
			fd_out = open(first_node[0].outfiles, O_WRONLY | O_TRUNC);
		else if (first_node[0].append == 3)
			fd_out = open(first_node[0].outfiles, O_WRONLY | O_APPEND);
		if (fd_out < 0)
		{
			g_exit_st = 13;
			write(2, first_node[0].outfiles, ft_strlen(first_node[0].outfiles));
			perror(": ");
		}
	}
	return (fd_out);
}
