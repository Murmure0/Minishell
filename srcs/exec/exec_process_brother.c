#include "../../includes/minishell.h"

int	path_finder_bro(t_node *middle_node, t_shell *shell)
{
	char	*tmp;
	int		i;

	if(middle_node[0].cmd)
	{
		tmp = middle_node[0].cmd[0];
		i = -1;
		while (shell->path[++i])
		{
			middle_node[0].cmd[0] = ft_strjoin(shell->path[i], tmp);
			if (!middle_node[0].cmd[0])
				return (-1);
			execve(middle_node[0].cmd[0], middle_node[0].cmd, shell->env);
			free(middle_node[0].cmd[0]);
		}
		middle_node[0].cmd[0] = tmp;
		execve(middle_node->cmd[0], middle_node->cmd, shell->env);
	}
	return (0);
}

int exec_cmd_bro(t_node *middle_node,t_shell *shell)
{
	if(!path_finder_bro(middle_node, shell))
	{
		//free_all(first_node); faire une bonne fct free
		return (-1);
	}
	return (0);
}

int	find_fd_in_bro(t_node *middle_node, t_exec *prev_exec_st)
{
	int	fd_in;

	fd_in = 0;
	if(middle_node->infiles || middle_node->infile_hd)
	{
		if (middle_node->infiles && middle_node->in_id == 2)
		{
			fd_in = open(middle_node->infiles, O_RDONLY);
			if (fd_in < 0)
			{
				write(2, middle_node->infiles, ft_strlen(middle_node->infiles));
				perror(": ");
				return (-1);
			}
		}
		else if (middle_node->in_id == 1 && !middle_node->invalid_infile)
			fd_in = middle_node->infile_hd;
	}
	else
		fd_in = prev_exec_st->pfd_in;
	return (fd_in);
}

void	pipe_case_bro(t_exec *exec_st_bro)
{
	int	pfd[2];

	if (pipe(pfd) < 0)
		perror(": ");
	exec_st_bro->pfd_out = pfd[1];
	exec_st_bro->pfd_in = pfd[0];
}

int	find_fd_out_bro(t_node *middle_node, t_exec *exec_st_bro)
{
	int	fd_out;

	fd_out = 1;
	if (exec_st_bro->num_cmd < middle_node->node_nb) //warning
		pipe_case_bro(exec_st_bro);
	if (exec_st_bro->num_cmd < middle_node->node_nb  && !middle_node->outfiles)
		fd_out = exec_st_bro->pfd_out;
	else if (middle_node->outfiles)
	{
		if (middle_node->append == 2)
			fd_out = open(middle_node->outfiles, O_WRONLY | O_TRUNC);
		else if (middle_node->append == 3)
			fd_out = open(middle_node->outfiles, O_WRONLY | O_APPEND);
		if (fd_out < 0)
		{
			write(2, middle_node->outfiles, ft_strlen(middle_node->outfiles));
			perror(": ");
			return (-1);
		}
	}
	return (fd_out);
}


t_exec	*init_exec_st_bro(t_node *middle_node, t_exec *prev_exec_st)
{
	t_exec	*exec_st_bro;

	exec_st_bro = malloc(sizeof(t_exec));
	if(!exec_st_bro)
	{
		write(2, "Memory allocation during middle process struct initialisation failed\n", 70);
		perror(": ");
	}
	exec_st_bro->num_cmd = prev_exec_st->num_cmd;
	exec_st_bro->fd_in = find_fd_in_bro(middle_node, prev_exec_st);
	if(exec_st_bro->fd_in < 0)
		return (NULL);
	exec_st_bro->fd_out = find_fd_out_bro(middle_node, exec_st_bro);
	if (exec_st_bro->fd_out < 0)
		return (NULL);
	return (exec_st_bro);
}

static void brother_fork_process(t_node *middle_node, t_exec *prev_exec_st, t_exec *exec_st_bro, t_shell *shell)
{
	if (exec_st_bro->fd_in > 0)
	{
		if (dup2(exec_st_bro->fd_in, STDIN_FILENO) < 0)
		{
			write(2, "Dup2 fdin brother process", 26);
			perror(": ");
			exit(EXIT_FAILURE);
		}
		close(exec_st_bro->fd_in);
	}
	if (exec_st_bro->fd_out > 1)
	{
		if (dup2(exec_st_bro->fd_out, STDOUT_FILENO) < 0)
		{
			write(2, "Dup2 fdout brother process", 26);
			perror(": ");
			exit(EXIT_FAILURE);
		}
		close(exec_st_bro->fd_out);
	}
	close(prev_exec_st->pfd_in);
	close(prev_exec_st->pfd_out);
	if (!find_builtin(middle_node, shell, 'y'))
	{
		exec_cmd_bro(middle_node, shell);
	}
		write(2, middle_node->cmd[0], 3);
		perror(" ");
}

// void	brother_process(pid_t prev_pid, t_exec *prev_exec_st, t_node *middle_node, t_shell *shell)
void	brother_process(t_exec *prev_exec_st, t_node *middle_node, t_shell *shell)
{
	pid_t	bro_pid;
	t_exec	*exec_st_bro;
	// int status;

	// status = 0;
	// waitpid(prev_pid, &status, WUNTRACED);
	exec_st_bro = init_exec_st_bro(middle_node, prev_exec_st);
	printf("\nxXx Processus num %d (Bro)xXx\nFDin : %d, FDout : %d\nPFDIN : %d PFDOUT : %d\n", exec_st_bro->num_cmd, exec_st_bro->fd_in, exec_st_bro->fd_out, exec_st_bro->pfd_in, exec_st_bro->pfd_out);
	bro_pid = fork();
	if (bro_pid < 0)
	{
		perror(": ");
		exit(EXIT_FAILURE); //exit ?
	}
	if(bro_pid == 0)
		brother_fork_process(middle_node, prev_exec_st, exec_st_bro, shell);

	close(prev_exec_st->pfd_in);
	// close(prev_exec_st->pfd_out);
	close(exec_st_bro->pfd_out); //
	free(prev_exec_st);
	if (exec_st_bro->num_cmd < (middle_node->node_nb - 1))
	{
		exec_st_bro->num_cmd++;
		brother_process(exec_st_bro, middle_node + 1, shell);
	}
	else
		parent_process(exec_st_bro, middle_node + 1, shell);
}