#include "../../includes/minishell.h"

int	find_fd_in(t_node *first_node)
{
	int	fd_in;
	int	i;

	i = -1;
	fd_in = 0;
	if (first_node[0].infiles[0].name == NULL)
	{
		printf("pas d'infile\n"); //a virer
		return (fd_in);
	}
	if (first_node[0].infiles[0].name)
	{
		printf("infile found\n"); //a virer
		while (first_node[0].infiles[++i].name)
		{
			fd_in = open(first_node[0].infiles[i].name, O_RDONLY);
			if (fd_in < 0)
			{
				write(2, first_node[0].infiles[i].name, ft_strlen(first_node[0].infiles[i].name));
				perror(": ");
				return (-1);
			}
			if (first_node[0].infiles[i + 1].name != NULL)
				close(fd_in);
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
	int	fd_out;
	int	i;

	i = -1;
	fd_out = 1;

	if ((first_node + 1) != (void *)0 && first_node[0].outfiles[0].name == NULL)
	{
		fd_out = pipe_case(exec_st);
		return(fd_out);
	}
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
	}
	exec_st->pfd_in = 0;
	exec_st->pfd_out = 0;
	exec_st->fd_in = find_fd_in(first_node);
	if(exec_st->fd_in < 0)
		return (NULL);
	exec_st->fd_out = find_fd_out(first_node, exec_st);
	if(exec_st->fd_out < 0)
		return (NULL);
	return (exec_st);
}

void	child_process(pid_t child_pid, t_exec *exec_st, t_node *first_node, t_shell shell)
{
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
		if(!find_builtin(first_node))
		{
			exec_cmd(first_node, shell);
			write(2, "Erreur post execution", 22);
			perror(": ");
			//free(exec_st);
			//close(STDOUT_FILENO);
			exit (errno);
		}
		exit(EXIT_SUCCESS);
	}
}
