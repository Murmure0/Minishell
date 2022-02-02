#include "../../includes/minishell.h"

int	find_fd_in(t_node *first_node)
{
	int	fd_in;
	int	i;

	i = -1;
	fd_in = 0;
	if (first_node[0].infiles[0].name == NULL)
	{
		printf("pas d'infile\n");
		return (fd_in);
	}
	if (first_node[0].infiles[0].name)
	{
		printf("infile found\n");
		while (first_node[0].infiles[++i].name)
		{
			fd_in = open(first_node[0].infiles[i].name, O_RDONLY);
			if (fd_in < 0)
				return (-1);
			if (first_node[0].infiles[i + 1].name != NULL)
				close(fd_in);
		}
	}
	return (fd_in);

}

int	find_fd_out(t_node *first_node)
{
	int	fd_out;
	int	i;

	i = -1;
	fd_out = 1;
	if (first_node[0].outfiles[0].name == NULL)
	{
		printf("outfile not found\n");
		return (fd_out);
	}
	if (first_node[0].outfiles[0].name)
	{
		printf("outfile found\n");
		while (first_node[0].outfiles[++i].name)
		{
			if (first_node[0].outfiles[i].redir == 2)
				fd_out = open(first_node[0].outfiles[i].name, O_WRONLY | O_TRUNC | O_CREAT, 0644);
			else if (first_node[0].outfiles[i].redir == 3)
				fd_out = open(first_node[0].outfiles[i].name, O_WRONLY | O_APPEND | O_CREAT, 0644);
			if (fd_out < 0)
				return (-1);
			if (first_node[0].outfiles[i + 1].name != NULL)
				close(fd_out);
		}
	}
	return (fd_out);
}

t_exec	*init_exec_st(t_node *first_node)
{
	t_exec	*exec_st;

	exec_st = malloc(sizeof(t_exec));
	if (!exec_st)
	{
		write(2, "Memory allocation for execution struct initialisation failed\n", 62);
		perror(": ");
		exit (errno);
	}
	exec_st->fd_in = find_fd_in(first_node);
	exec_st->fd_out = find_fd_out(first_node);
	printf("outfile : %d\n", exec_st->fd_out);
	return (exec_st);
}

void	child_process(pid_t child_pid, t_exec *exec_st, t_node *first_node, t_shell shell)
{
	exec_st->fd_out = 0; //a virer

	if (child_pid == 0)
	{
		if (exec_st->fd_in > 0)
		{
			if (dup2(exec_st->fd_in, STDIN_FILENO) < 0)
			{
				perror(": ");
				exit (errno);
			}
			close(exec_st->fd_in);
		}
		/*
		if (dup2(fds[1], STDOUT_FILENO) < 0)
			error_message(7);
		close(fds[0]);
		close(fds[1]);*/

		exec_cmd(first_node, shell);
		write(2, "Erreur post execution", 22);
		perror(": ");
		free(exec_st);
		//close(STDOUT_FILENO);
		exit (errno);
	}
}
