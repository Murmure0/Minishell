#include "../../includes/minishell.h"

void parent_process(pid_t child_pid, t_exec *exec_st, t_node *second_node, t_shell *shell)
{
	(void)exec_st;
	(void)second_node;
	(void)shell;

	int		status;


//initialiser les fd in et out
	status = 0;
	waitpid(child_pid, &status, 0);
}