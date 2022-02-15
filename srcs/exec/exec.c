#include "../../includes/minishell.h"

int	exec(t_node *first_node, t_shell *shell)
{
	pid_t	child_pid;
	t_exec	*exec_st;
	int status;

	status = 0;
	exec_st = init_exec_st(first_node);
	if (!exec_st)
		return (-1);
	if (first_node->node_nb == 1 && find_builtin(first_node, shell, 'n'))
		redir_solo_builtin(first_node, shell, exec_st);
	else
	{
		child_pid = exec_child_proc(first_node, shell, exec_st);
		if (first_node[0].node_nb == 2)
			parent_process(child_pid, exec_st, first_node + 1, shell);
		else if (first_node[0].node_nb > 2)
			brother_process(child_pid, exec_st, first_node + 1, shell);
	}
	waitpid(-1, &status, 0);
	return (0);
}
