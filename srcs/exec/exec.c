#include "../../includes/minishell.h"

int exec(t_node *first_node, t_shell shell)
{
	pid_t	child_pid;
	int		status;
	t_exec *exec_st;

	exec_st = init_exec_st(first_node);
	if (!exec_st)
		return (-1);
	status = 0;
	child_pid = fork();
	if (child_pid < 0)
	{
		write(2, "Child fork failed", 18);
		perror(": ");
		exit (errno);
	}
	if (child_pid == 0)
		{
			//printf("valeur pid ; %d\n", child_pid);
			child_process(child_pid, exec_st, first_node, shell);
		}
	waitpid(child_pid, &status, 0);
	//if (first_node + 1 == NULL)

	/*else if (first_node + 1 && first_node + 2)
		printf("brother process\n");
		//brother_process();
	else
		printf("parent process\n");
		//parent_process();*/
	return(0);
}
