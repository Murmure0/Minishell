#include "../../includes/minishell.h"

static void	brother_fork_process(t_node *middle_node, t_exec *prev_exec_st,
	t_exec *exec_st_bro, t_shell *shell)
{
	if (exec_st_bro->fd_in > 0)
		fd_dup(exec_st_bro->fd_in, STDIN_FILENO);
	if (exec_st_bro->fd_out > 1)
		fd_dup(exec_st_bro->fd_out, STDOUT_FILENO);
	close(prev_exec_st->pfd_in);
	close(prev_exec_st->pfd_out);
	if (!find_builtin(middle_node, shell, 'y'))
	{
		exec_cmd(middle_node, shell);
		write(2, middle_node->cmd[0], 3);
		perror(" ");
	}
}

void	brother_process(t_exec *prev_exec_st, t_node *middle_node,
	t_shell *shell)
{
	pid_t	bro_pid;
	t_exec	*exec_st_bro;

	exec_st_bro = init_exec_st_bro(middle_node, prev_exec_st);
	bro_pid = fork();
	if (bro_pid < 0)
	{
		write(2, "Middle fork failed", 19);
		perror(": ");
	}
	if (bro_pid == 0)
		brother_fork_process(middle_node, prev_exec_st, exec_st_bro, shell);
	close(prev_exec_st->pfd_in);
	close(exec_st_bro->pfd_out);
	free(prev_exec_st);
	if (exec_st_bro->num_cmd < (middle_node->node_nb - 1))
	{
		exec_st_bro->num_cmd++;
		brother_process(exec_st_bro, middle_node + 1, shell);
	}
	else
		parent_process(exec_st_bro, middle_node + 1, shell);
}
