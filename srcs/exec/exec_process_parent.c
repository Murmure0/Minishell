/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_process_parent.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 13:22:16 by mberthet          #+#    #+#             */
/*   Updated: 2022/03/07 17:18:08 by mberthet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_exit_st;

static void	parent_fork_process(t_node *last_node, t_exec *exec_st,
	t_exec *exec_st_parent, t_shell *shell)
{
	if (exec_st_parent->fd_in < 0 || exec_st_parent->fd_out < 0)
		exit (0);
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

int	fork_failed(t_exec *prev_exec_st, t_exec *exec_st_parent, t_node *last_node)
{
	g_exit_st = -1;
	write(1, "minishell: ", 12);
	write(1, last_node->cmd[0], ft_strlen(last_node->cmd[0]));
	write(1, " : fork failed.\n", 16);
	free(prev_exec_st);
	free(exec_st_parent);
	return (-1);
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
		fork_failed(prev_exec_st, exec_st_parent, last_node);
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
