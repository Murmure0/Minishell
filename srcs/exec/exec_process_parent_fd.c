/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_process_parent_fd.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 17:00:48 by mberthet          #+#    #+#             */
/*   Updated: 2022/03/07 17:06:51 by mberthet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_exit_st;

int	find_fd_in_parent(t_node *last_node, t_exec *exec_st)
{
	int	fd_in;

	fd_in = 0;
	if (last_node->infiles || last_node->infile_hd)
	{
		if (last_node->infiles && last_node->in_id == 2)
		{
			fd_in = open(last_node->infiles, O_RDONLY);
			if (fd_in < 0)
			{
				g_exit_st = 13;
				write(2, last_node->infiles, ft_strlen(last_node->infiles));
				perror(": ");
			}
		}
		else if (last_node->in_id == 1 && !last_node->invalid_infile)
			fd_in = last_node->infile_hd;
	}
	else
		fd_in = exec_st->pfd_in;
	return (fd_in);
}

int	find_fd_out_parent(t_node *last_node)
{
	int	fd_out;

	fd_out = 1;
	if (last_node[0].outfiles)
	{
		if (last_node[0].append == 2)
			fd_out = open(last_node[0].outfiles, O_WRONLY | O_TRUNC);
		else if (last_node[0].append == 3)
			fd_out = open(last_node[0].outfiles, O_WRONLY | O_APPEND);
		if (fd_out < 0)
		{
			g_exit_st = 13;
			write(2, last_node[0].outfiles, ft_strlen(last_node[0].outfiles));
			perror(": ");
		}
	}
	return (fd_out);
}

t_exec	*init_exec_st_parent(t_node *last_node, t_exec *exec_st)
{
	t_exec	*exec_st_parent;

	exec_st_parent = malloc(sizeof(t_exec));
	if (!exec_st_parent)
	{
		g_exit_st = -1;
		write(2, "Memory allocation failed\n", 26);
		return (NULL);
	}
	exec_st_parent->pfd_in = 0;
	exec_st_parent->pfd_out = 0;
	exec_st_parent->fd_in = find_fd_in_parent(last_node, exec_st);
	exec_st_parent->fd_out = find_fd_out_parent(last_node);
	return (exec_st_parent);
}
