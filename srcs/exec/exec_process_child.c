#include "../../includes/minishell.h"

int	find_fd_in(t_node *first_node)
{
	int	fd_in;

	fd_in = 0;
	if (first_node[0].infiles)
	{
		// printf("infile found\n"); //a virer
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

int pipe_case(t_exec *exec_st)
{
	int	pfd[2];

	if (pipe(pfd) < 0)
		perror(": ");
	exec_st->pfd_out = pfd[1]; //doit etre close egalement ?
	exec_st->pfd_in = pfd[0];
	close(pfd[0]); //close ici ou dans exec ? peut etre source de pb +tard
	return(pfd[1]);
}

int	find_fd_out(t_node *first_node, t_exec *exec_st)
{
	(void)exec_st;
	int	fd_out;
	// int	i;

	// i = -1;
	fd_out = 1;

	// if ((first_node + 1) != (void *)0 && first_node[0].outfiles == NULL)
	// {
	// 	fd_out = pipe_case(exec_st);
	// 	return(fd_out);
	// }
	if (first_node[0].outfiles)
	{
		// printf("outfile found\n");
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

t_exec	*init_exec_st(t_node *first_node)
{
	t_exec	*exec_st;

	exec_st = malloc(sizeof(t_exec));
	if (!exec_st)
	{
		write(2, "Memory allocation for execution struct initialisation failed\n", 62);
		perror(": ");
	}
	exec_st->pfd_in = 0;
	exec_st->pfd_out = 0;
	exec_st->fd_in = find_fd_in(first_node);
	// printf("exec fd in : %d\n",exec_st->fd_in);
	if(exec_st->fd_in < 0)
		return (NULL);
	exec_st->fd_out = find_fd_out(first_node, exec_st);
	// printf("exec fd out : %d\n",exec_st->fd_out);
	if(exec_st->fd_out < 0)
		return (NULL);
	return (exec_st);
}

void	child_process(pid_t child_pid, t_exec *exec_st, t_node *first_node, t_shell *shell)
{
	(void)exec_st;
	if (child_pid == 0)
	{
		// if (exec_st->fd_in > 0)
		// {
		// 	if (dup2(exec_st->fd_in, STDIN_FILENO) < 0)
		// 	{
		// 		close(exec_st->fd_in);
		// 		perror(": ");
		// 		exit (errno);
		// 	}
		// 	close(exec_st->fd_in);
		// }
		// printf("fd out : %d", exec_st->fd_out);
		// if(exec_st->fd_out > 1)
		// {
		// 	if (dup2(exec_st->fd_out, STDOUT_FILENO) < 0)
		// 	{
		// 		close(exec_st->fd_in);
		// 		close(exec_st->fd_out);
		// 		perror(": ");
		// 		exit (errno);
		// 	}
		// 	close(exec_st->fd_out);
		// }
		// printf("exec : %s\n", first_node[0].cmd[0]);
		if(!find_builtin(first_node, shell))
		{
			exec_cmd(first_node, *shell);
			write(2, "Erreur post execution", 22);
			perror(": ");
			//free(exec_st);
			//close(STDOUT_FILENO);
			// exit (errno);
		}
		// exit(EXIT_SUCCESS);
	}
}
