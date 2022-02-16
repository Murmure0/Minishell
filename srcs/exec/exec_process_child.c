#include "../../includes/minishell.h"

int	find_fd_in(t_node *first_node)
{
	int	fd_in;

	fd_in = 0;
	if (first_node[0].infiles)
	{
		fd_in = open(first_node[0].infiles, O_RDONLY);
		if (fd_in < 0)
		{
			write(2, first_node[0].infiles, ft_strlen(first_node[0].infiles));
			perror(": ");
			return (-1);
		}
	}
	return (fd_in);
}

void	pipe_case(t_exec *exec_st)
{
	int	pfd[2];

	if (pipe(pfd) < 0)
		perror(": ");
	exec_st->pfd_out = pfd[1];
	exec_st->pfd_in = pfd[0];
	exec_st->num_cmd++;
}

int	find_fd_out(t_node *first_node, t_exec *exec_st)
{
	int	fd_out;

	fd_out = 1;
	if (first_node[0].node_nb > 1)
		pipe_case(exec_st);
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
			write(2, first_node[0].outfiles, ft_strlen(first_node[0].outfiles));
			perror(": ");
			return (-1);
		}
	}
	return (fd_out);
}

void	child_process(pid_t child_pid, t_exec *exec_st, t_node *first_node,
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
			write(2, "Erreur post execution child ", 29);
			perror(": ");
			exit(EXIT_FAILURE);
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
		write(2, "Child fork failed", 18);
		perror(": ");
	}
	if (child_pid == 0)
		child_process(child_pid, exec_st, first_node, shell);
	if (first_node[0].node_nb == 1)
	{
		waitpid(child_pid, &status, 0);
	}
	printf("\nXxXFin child procXxX\nPdfin : %d, Pdfout : %d\nEnvoyer apres: fd_out : %d\n", exec_st->pfd_in, exec_st->pfd_out, exec_st->fd_out);
	return (child_pid);
}
