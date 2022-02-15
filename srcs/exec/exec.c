#include "../../includes/minishell.h"

int	exec(t_node *first_node, t_shell *shell)
{
	pid_t	child_pid;
	t_exec	*exec_st;

	exec_st = init_exec_st(first_node);
	if (!exec_st)
		return (-1);
	if (first_node->node_nb == 1 && find_builtin(first_node, shell, 'n'))
		redir_solo_builtin(first_node, shell, exec_st);
	else
	{
		child_pid = exec_child_proc(first_node, shell, exec_st);
		if (first_node[0].node_nb == 2)
		{
			printf("1 seul pipe\n");
			parent_process(child_pid, exec_st, first_node + 1, shell);
		}
		else if (first_node[0].node_nb > 2)
		{
			printf("plusieurs pipes\n");
			brother_process(child_pid, exec_st, first_node + 1, shell);
		}
	}
	return (0);
}
