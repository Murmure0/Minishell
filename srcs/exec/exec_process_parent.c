/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_process_parent.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 13:22:16 by mberthet          #+#    #+#             */
/*   Updated: 2022/03/02 16:55:33 by mberthet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_exit_st;

static int	find_fd_in_parent(t_node *last_node, t_exec *exec_st)
{
	int	fd_in;

	fd_in = 0;
		printf("infile : %s\n", last_node->infiles);
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

static int	find_fd_out_parent(t_node *last_node)
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

static t_exec	*init_exec_st_parent(t_node *last_node, t_exec *exec_st)
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

static void	parent_fork_process(t_node *last_node, t_exec *exec_st,
	t_exec *exec_st_parent, t_shell *shell)
{
	if (exec_st_parent->fd_in < 0 || exec_st_parent->fd_out < 0)
		exit (0);
	printf("Valleur fdin : %d\n",exec_st_parent->fd_in);
	if (exec_st_parent->fd_in > 0)
		fd_dup(exec_st_parent->fd_in, STDIN_FILENO);
	if (exec_st_parent->fd_out > 1)
		fd_dup(exec_st_parent->fd_out, STDOUT_FILENO);
	close(exec_st->pfd_in);
	close(exec_st->pfd_out);
	free(exec_st);
	free(exec_st_parent);
	if (!find_builtin(last_node, shell, 'y'))
		path_finder(last_node, shell);

}

int	parent_process(t_exec *prev_exec_st, t_node *last_node, t_shell *shell)
{
	t_exec	*exec_st_parent;
	pid_t	parent_pid;

	exec_st_parent = init_exec_st_parent(last_node, prev_exec_st);
	if (!exec_st_parent)
	{
		free(prev_exec_st);
		return (-1);
	}
	parent_pid = fork();
	if (parent_pid < 0)
	{
		g_exit_st = -1;
		write(1, "minishell: ", 12);
		write(1, last_node->cmd[0], ft_strlen(last_node->cmd[0]));
		write(1, " : fork failed.\n", 16);
		free(prev_exec_st);
		free(exec_st_parent);
		return (-1);
	}
	if (parent_pid == 0)
		parent_fork_process(last_node, prev_exec_st, exec_st_parent, shell);
	close(prev_exec_st->pfd_in);
	close(prev_exec_st->pfd_out);
	free(prev_exec_st);
	free(exec_st_parent);
	return (0);
}
