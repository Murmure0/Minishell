/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_process_child.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maelle <maelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 13:22:02 by mberthet          #+#    #+#             */
/*   Updated: 2022/03/14 17:31:18 by maelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_exit_st;

static void	child_process(t_exec *exec_st, t_node *first_node,
		t_shell *shell)
{
	signal(SIGQUIT, handle_sig_fork);
	signal(SIGINT, handle_sig_fork);
	if (exec_st->fd_in < 0 || exec_st->fd_out < 0)
		exit(0);
	if (exec_st->fd_in > 0)
		fd_dup(exec_st->fd_in, STDIN_FILENO);
	if (exec_st->fd_out > 1)
		fd_dup(exec_st->fd_out, STDOUT_FILENO);
	if (first_node[0].node_nb > 1)
	{
		close(exec_st->pfd_in);
		close(exec_st->pfd_out);
	}
	if (!find_builtin(first_node, shell, 'y'))
		path_finder(first_node, shell);
}

static void	free_signal(t_exec *exec_st, int child_pid, int status)
{
	free(exec_st);
	waitpid(child_pid, &status, 0);
	if (WIFEXITED(status))
		g_exit_st = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_exit_st = 128 + WTERMSIG(status);
}

int	exec_child_proc(t_node *first_node, t_shell *shell, t_exec *exec_st)
{
	int		status;
	pid_t	child_pid;

	status = 0;
	child_pid = fork();
	if (child_pid < 0)
	{
		g_exit_st = -1;
		write(1, "minishell: ", 12);
		write(1, first_node->cmd[0], ft_strlen(first_node->cmd[0]));
		write(1, " : fork failed.\n", 16);
		return (-1);
	}
	if (child_pid == 0)
		child_process(exec_st, first_node, shell);
	if (exec_st->pfd_out > 0)
		close(exec_st->pfd_out);
	if (first_node[0].node_nb == 1)
		free_signal(exec_st, child_pid, status);
	return (0);
}
