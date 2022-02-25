#include "../../includes/minishell.h"

static int	execution(t_node *first_node, t_shell *shell, t_exec *exec_st,
		pid_t child_pid)
{
	int		nb_cmd;

	nb_cmd = first_node[0].node_nb;
	signal(SIGQUIT, handle_sig_fork);
	signal(SIGINT, handle_sig_fork);
	child_pid = exec_child_proc(first_node, shell, exec_st);
	if (nb_cmd == 2)
		parent_process(exec_st, first_node + 1, shell);
	else if (nb_cmd > 2)
		brother_process(exec_st, first_node + 1, shell);
	return (1);
}

int	exec(t_node *first_node, t_shell *shell)
{
	pid_t	child_pid;
	t_exec	*exec_st;
	int		nb_cmd;
	int		status;

	status = 0;
	child_pid = 0;
	nb_cmd = first_node[0].node_nb;
	exec_st = init_exec_st(first_node);
	if (!exec_st)
		return (-1);
	if (nb_cmd == 1 && find_builtin(first_node, shell, 'n'))
		redir_solo_builtin(first_node, shell, exec_st);
	else
		execution(first_node, shell, exec_st, child_pid);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &shell->termios_p);
	if (nb_cmd > 1)
		while ((nb_cmd--) > 0)
			wait(&status);
	return (0);
}
