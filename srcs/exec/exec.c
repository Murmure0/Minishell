#include "../../includes/minishell.h"

int exec(t_node *first_node, t_shell *shell)
{
	// int i = -1;
	pid_t	*child_pid;
	int		status;
	t_exec *exec_st;

	child_pid = malloc(sizeof(pid_t) * 1);
	*child_pid = 1;
	exec_st = init_exec_st(first_node);
	if (!exec_st)
		return (-1);
	printf("find fd debut exec nodes : %d\n",first_node[0].node_nb);

	if (!find_builtin(first_node, shell))
	{
		printf("exec\n");
		status = 0;
		*child_pid = fork();
		if (child_pid < 0)
		{
			write(2, "Child fork failed", 18);
			perror(": ");
			// exit (errno);
		}
		if (*child_pid == 0)
			child_process(*child_pid, exec_st, first_node, shell);
		if (first_node[0].node_nb == 1) //on ne met un waitpid que si on a pas de pipe, sinon il sera au debut du processus suivant
		{
			printf("nb nodes au waitpid: %d\n",first_node[0].node_nb);
			waitpid(*child_pid, &status, 0);
		}
	}

	if (first_node[0].node_nb == 2)
	{
		printf("parent process\n");
		parent_process(*child_pid, NULL, NULL, NULL);
	}
	
	/*else if (first_node[0].node_nb > 2)
		printf("brother process\n");
		//brother_process();*/
	return(0);
}
