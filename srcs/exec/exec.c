#include "../../includes/minishell.h"

int	exec(t_node *first_node, t_shell *shell)
{
	pid_t	child_pid;
	t_exec	*exec_st;
	int		nb_cmd;
	int		status;

	status = 0;
	nb_cmd = first_node[0].node_nb;
	printf("nb cmd : %d", nb_cmd);
	exec_st = init_exec_st(first_node);
	if (!exec_st)
		return (-1);
	if (first_node->node_nb == 1 && find_builtin(first_node, shell, 'n'))
		redir_solo_builtin(first_node, shell, exec_st);
	else
	{
		write(2, "Giello world!\n", 14);
		child_pid = exec_child_proc(first_node, shell, exec_st);
		if (nb_cmd == 2)
			parent_process(exec_st, first_node + 1, shell);
		else if (nb_cmd > 2)
			brother_process(exec_st, first_node + 1, shell);
	}
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &shell->termios_p);
	write(2, "Miello world!\n", 14);
	// wait(&status);
	while ((nb_cmd) > 0)
	{
		wait(&status);
		nb_cmd--;
		printf("nb cmd wait : %d\n", nb_cmd);
	}
	// wait(&status);
	write(2, "Hello world!\n", 13);
	return (0);
}
