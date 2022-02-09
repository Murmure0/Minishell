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
	printf("Valeur de PFDIN dans pipe case : %d\n", pfd[0]);
	//close(pfd[0]); //close ici ou dans exec ? peut etre source de pb +tard
	return(pfd[1]);
}

int	find_fd_out(t_node *first_node, t_exec *exec_st)
{
	(void)exec_st;
	int	fd_out;

	fd_out = 1;

	// printf("find fd outnb nodes : %d\n",first_node[0].node_nb);
	if (first_node[0].node_nb > 1 && !first_node->outfiles)
	{
		fd_out = pipe_case(exec_st);
		printf("FD out PFD : %d\n", fd_out);
		printf("FD in PFD : %d\n", exec_st->pfd_in);
		return(fd_out);
	}

	else if (first_node[0].outfiles)
	{
		// printf("outfile found\n");
		if (first_node[0].append == 2)
			fd_out = open(first_node[0].outfiles, O_WRONLY | O_TRUNC);
		else if (first_node[0].append == 3)
			fd_out = open(first_node[0].outfiles, O_WRONLY | O_APPEND);
		printf("FD out outfiles process child : %d\n", fd_out);
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
		if (exec_st->fd_in > 0)
		{
			if (dup2(exec_st->fd_in, STDIN_FILENO) < 0)
			{
				close(exec_st->fd_in);
				perror(": ");
				exit (errno);
			}
			close(exec_st->fd_in);
		}
		printf("child process fd out : %d\n", exec_st->fd_out);
		if(exec_st->fd_out > 1)
		{
			if (dup2(exec_st->fd_out, STDOUT_FILENO) < 0)
			{
				close(exec_st->fd_in);
				close(exec_st->fd_out);
				perror(": ");
				exit (errno);
			}
			close(exec_st->fd_out);
		}
		// printf("exec : %s\n", first_node[0].cmd[0]);
		if(!find_builtin(first_node, shell))
		{
			exec_cmd(first_node, *shell);
			write(2, "Erreur post execution child ", 29);
			perror(": ");
			//free(exec_st);
			//close(STDOUT_FILENO);
			// exit (errno);
		}
		// exit(EXIT_SUCCESS);
	}
}
