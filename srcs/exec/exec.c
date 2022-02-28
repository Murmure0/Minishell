#include "../../includes/minishell.h"

extern int	g_exit_st;

static int	execution(t_node *first_node, t_shell *shell, t_exec *exec_st)
{
	int		nb_cmd;

	nb_cmd = first_node[0].node_nb;
	signal(SIGQUIT, handle_sig_fork);
	signal(SIGINT, handle_sig_fork);
	exec_child_proc(first_node, shell, exec_st);
	if (nb_cmd == 2)
		parent_process(exec_st, first_node + 1, shell);
	else if (nb_cmd > 2)
		brother_process(exec_st, first_node + 1, shell);
	return (1);
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
	if (nb_cmd == 1 && find_builtin(first_node, shell, 'n'))
		redir_solo_builtin(first_node, shell, exec_st);
	else
		execution(first_node, shell, exec_st);
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
