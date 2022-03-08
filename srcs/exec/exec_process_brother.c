/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_process_brother.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 11:22:58 by mberthet          #+#    #+#             */
/*   Updated: 2022/03/07 16:38:59 by mberthet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_exit_st;

static void	brother_fork_process(t_node *middle_node, t_exec *prev_exec_st,
	t_exec *exec_st_bro, t_shell *shell)
{
	if (exec_st_bro->fd_in > 0)
		fd_dup(exec_st_bro->fd_in, STDIN_FILENO);
	if (exec_st_bro->fd_out > 1)
		fd_dup(exec_st_bro->fd_out, STDOUT_FILENO);
	close(prev_exec_st->pfd_in);
	close(prev_exec_st->pfd_out);
	if (!find_builtin(middle_node, shell, 'y'))
		path_finder(middle_node, shell);
}

static int	bro_or_parent_proc(t_exec *exec_st_bro, t_node *middle_node,
		t_shell *shell, t_exec *prev_exec_st)
{
	close(prev_exec_st->pfd_in);
	close(exec_st_bro->pfd_out);
	free(prev_exec_st);
	if (exec_st_bro->num_cmd < (middle_node->node_nb - 1))
	{
		exec_st_bro->num_cmd++;
		if (brother_process(exec_st_bro, middle_node + 1, shell) < 0)
			return (-1);
	}
	else
		if (parent_process(exec_st_bro, middle_node + 1, shell) < 0)
			return (-1);
	return (0);
}

static void	fork_failed(t_node *middle_node, t_exec *prev_exec_st,
		t_exec *exec_st_bro)
{
	g_exit_st = -1;
	write(1, "minishell: ", 12);
	write(1, middle_node->cmd[0], ft_strlen(middle_node->cmd[0]));
	write(1, " : fork failed.\n", 16);
	free(prev_exec_st);
	free(exec_st_bro);
}

int	brother_process(t_exec *prev_exec_st, t_node *middle_node,
	t_shell *shell)
{
	pid_t	bro_pid;
	t_exec	*exec_st_bro;

	exec_st_bro = init_exec_st_bro(middle_node, prev_exec_st);
	if (!exec_st_bro)
	{
		free(prev_exec_st);
		return (-1);
	}
	bro_pid = fork();
	if (bro_pid < 0)
	{
		fork_failed(middle_node, prev_exec_st, exec_st_bro);
		return (-1);
	}
	if (bro_pid == 0)
		brother_fork_process(middle_node, prev_exec_st, exec_st_bro, shell);
	if (bro_or_parent_proc(exec_st_bro, middle_node, shell, prev_exec_st) < 0)
		return (-1);
	return (0);
}
