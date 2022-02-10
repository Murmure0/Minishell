#include "../../includes/minishell.h"

int	exec(t_node *first_node, t_shell *shell)
{
	pid_t	child_pid;
	t_exec	*exec_st;

	exec_st = init_exec_st(first_node);
	if (!exec_st)
		return (-1);
	if (!find_builtin(first_node, shell))
		child_pid = exec_child_proc(first_node, shell, exec_st);
	if (first_node[0].node_nb == 2)
	{
		printf("parent process\n");
		parent_process(child_pid, exec_st, first_node + 1, shell);
	}
	else if (first_node[0].node_nb > 2)
	{
		printf("brother process\n");
		brother_process(child_pid, exec_st, first_node + 1, shell);
	}
	return(0);
}
