#include "../../includes/minishell.h"

extern int	g_exit_st;

int	find_fd_in(t_node *first_node)
{
	int	fd_in;

	fd_in = 0;
	if (first_node[0].infiles && first_node->in_id == 2)
	{
		fd_in = open(first_node[0].infiles, O_RDONLY);
		if (fd_in < 0)
		{
			g_exit_st = 1;
			write(2, first_node[0].infiles, ft_strlen(first_node[0].infiles));
			perror(": ");
			return (-1);
		}
	}
	else if (first_node->in_id == 1 && !first_node->invalid_infile)
		fd_in = first_node->infile_hd;
	return (fd_in);
}

static int	pipe_case(t_exec *exec_st)
{
	int	pfd[2];

	if (pipe(pfd) < 0)
	{
		g_exit_st = -1;
		perror(": ");
		return (g_exit_st);
	}
	exec_st->pfd_out = pfd[1];
	exec_st->pfd_in = pfd[0];
	exec_st->num_cmd++;
	return (0);
}

int	find_fd_out(t_node *first_node, t_exec *exec_st)
{
	int	fd_out;

	fd_out = 1;
	if (first_node[0].node_nb > 1)
		if (pipe_case(exec_st) < 0)
			return (g_exit_st);
	if (first_node[0].node_nb > 1 && !first_node[0].outfiles)
		fd_out = exec_st->pfd_out;
	else if (first_node[0].outfiles)
	{
		if (first_node[0].append == 2)
			fd_out = open(first_node[0].outfiles, O_WRONLY | O_TRUNC);
		else if (first_node[0].append == 3)
			fd_out = open(first_node[0].outfiles, O_WRONLY | O_APPEND);
		if (fd_out < 0)
		{
			g_exit_st = -1;
			write(2, first_node[0].outfiles, ft_strlen(first_node[0].outfiles));
			perror(": ");
			return (g_exit_st);
		}
	}
	return (fd_out);
}

static void	child_process(pid_t child_pid, t_exec *exec_st, t_node *first_node,
		t_shell *shell)
{
	if (child_pid == 0)
	{
		if (exec_st->fd_in > 0)
			fd_dup(exec_st->fd_in, STDIN_FILENO);
		if (exec_st->fd_out > 1)
			fd_dup(exec_st->fd_out, STDOUT_FILENO);
		if (first_node[0].node_nb > 1)
		{
			close(exec_st->pfd_in);
			close(exec_st->pfd_out);
		}
		if (!find_builtin(first_node, shell, 'y'))
		{
			exec_cmd(first_node, shell);
		}
	}
}

pid_t	exec_child_proc(t_node *first_node, t_shell *shell, t_exec *exec_st)
{
	int		status;
	pid_t	child_pid;

	status = 0;
	child_pid = fork();
	if (child_pid < 0)
	{
		g_exit_st = -1;
		perror(": ");
	}
	if (child_pid == 0)
		child_process(child_pid, exec_st, first_node, shell);
	if (exec_st->pfd_out > 0)
		close(exec_st->pfd_out);
	if (first_node[0].node_nb == 1)
	{
		free(exec_st);
		waitpid(child_pid, &status, 0);
		if (WIFEXITED(status))
			g_exit_st = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			g_exit_st = 128 + WTERMSIG(status);
	}
	return (child_pid);
}
