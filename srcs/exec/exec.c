/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 11:14:49 by mberthet          #+#    #+#             */
/*   Updated: 2022/03/08 17:57:50 by mberthet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
//pouet
extern int	g_exit_st;

static int	execution(t_node *first_node, t_shell *shell, t_exec *exec_st)
{
	int		nb_cmd;

	nb_cmd = first_node[0].node_nb;
	signal(SIGQUIT, handle_sig_fork);
	signal(SIGINT, handle_sig_fork);
	if (exec_child_proc(first_node, shell, exec_st) < 0)
		return (-1);
	if (nb_cmd == 2)
	{
		if (parent_process(exec_st, first_node + 1, shell) < 0)
			return (-1);
	}
	else if (nb_cmd > 2)
	{
		if (brother_process(exec_st, first_node + 1, shell) < 0)
			return (-1);
	}
	return (1);
}

static int	id_cmd_exec(int nb_cmd, t_node *first_node, t_shell *shell,
	t_exec *exec_st)
{
	if (nb_cmd == 1 && find_builtin(first_node, shell, 'n'))
	{
		if (redir_solo_builtin(first_node, shell, exec_st) < 0)
			return (-1);
	}
	else
	{
		if (execution(first_node, shell, exec_st) < 0)
			return (-1);
	}
	return (0);
}

int	exec(t_node *first_node, t_shell *shell)
{
	t_exec	*exec_st;
	int		nb_cmd;
	int		status;

	nb_cmd = first_node[0].node_nb;
	exec_st = init_exec_st(first_node);
	if (!exec_st)
		return (-1);
	if (id_cmd_exec(nb_cmd, first_node, shell, exec_st) < 0)
		return (-1);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &shell->termios_p);
	if (nb_cmd > 1)
	{
		while ((nb_cmd--) > 0)
			wait(&status);
		if (WIFEXITED(status))
			g_exit_st = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			g_exit_st = 128 + WTERMSIG(status);
	}
	return (0);
}
