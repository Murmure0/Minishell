#include "../../includes/minishell.h"

int	path_finder_parent(t_node *last_node, t_shell *shell)
{
	char	*tmp;
	int		i;

	if(last_node[0].cmd)
	{
		tmp = last_node[0].cmd[0];
		i = -1;
		while (shell->path[++i])
		{
			last_node[0].cmd[0] = ft_strjoin(shell->path[i], tmp);
			if (!last_node[0].cmd[0])
				return (-1);
			execve(last_node[0].cmd[0], last_node[0].cmd, shell->env);
			free(last_node[0].cmd[0]);
		}
		last_node[0].cmd[0] = tmp;
		execve(last_node->cmd[0], last_node->cmd, shell->env);
	}
	return (0);
}

int	exec_cmd_parent(t_node *last_node, t_shell *shell)
{
	if (!path_finder_parent(last_node, shell))
	{
		// free(); faire une bonne fct free
		return (-1);
	}
	return (0);
}

int	find_fd_in_parent(t_node *last_node, t_exec *exec_st)
{
	int	fd_in;

	fd_in = 0;
	if (last_node->infiles || last_node->infile_hd)
	{
		printf("valeur inid : %d\n", last_node->in_id);
		if (last_node->infiles && last_node->in_id == 2)
		{
			write(1, "POUET\n",6);
			fd_in = open(last_node->infiles, O_RDONLY);
			if (fd_in < 0)
			{
				write(2, last_node->infiles, ft_strlen(last_node->infiles));
				perror(": ");
				return (-1);
			}
		}
		else if (last_node->in_id == 1 && !last_node->invalid_infile)
			fd_in = last_node->infile_hd;
	}
	else
		fd_in = exec_st->pfd_in;
	return (fd_in);
}

int	find_fd_out_parent(t_node *last_node)
{
	int	fd_out;

	fd_out = 1;

	if (last_node[0].outfiles)
	{
		if (last_node[0].append == 2)
			fd_out = open(last_node[0].outfiles, O_WRONLY | O_TRUNC);
		else if (last_node[0].append == 3)
			fd_out = open(last_node[0].outfiles, O_WRONLY | O_APPEND);
		if (fd_out < 0)
		{
			write(2, last_node[0].outfiles, ft_strlen(last_node[0].outfiles));
			perror(": ");
			return (-1);
		}
	}
	return (fd_out);
}

t_exec	*init_exec_st_parent(t_node *last_node, t_exec *exec_st)
{
	t_exec	*exec_st_parent;

	exec_st_parent = malloc(sizeof(t_exec));
	exec_st_parent->pfd_in = 0;
	exec_st_parent->pfd_out = 0;
	if (!exec_st_parent)
	{
		write(2, "Memory allocation for last execution struct initialisation failed\n", 67);
		perror(": ");
	}
	exec_st_parent->fd_in = find_fd_in_parent(last_node, exec_st);
	if(exec_st_parent->fd_in < 0)
		return (NULL);
	exec_st_parent->fd_out = find_fd_out_parent(last_node);
	if(exec_st_parent->fd_out < 0)
		return (NULL);
	// printf("\nXxXRecup entree parent procXxX\nFd_in : %d, Fd_out : %d\n", exec_st_parent->fd_in, exec_st_parent->fd_out);
	return (exec_st_parent);
}

static void parent_fork_process(t_node *last_node, t_exec *exec_st, t_exec *exec_st_parent, t_shell *shell)
{
	if (exec_st_parent->fd_in > 0)
	{
		if (dup2(exec_st_parent->fd_in, STDIN_FILENO) < 0)
		{
			write(2, "Dup2 fdin parent ", 18);
			perror(": ");
			exit(EXIT_FAILURE);
		}
		close(exec_st_parent->fd_in);
	}
	if (exec_st_parent->fd_out > 1)
	{
		if (dup2(exec_st_parent->fd_out, STDOUT_FILENO) < 0)
		{
			write(2, "Dup2 fdout parent ", 19);
			perror(": ");
			exit(EXIT_FAILURE);
		}
		close(exec_st_parent->fd_out);
	}
	close(exec_st->pfd_in);
	close(exec_st->pfd_out);
	if (!find_builtin(last_node, shell, 'y'))
	{
		exec_cmd_parent(last_node, shell);
	}
		write(2, "Erreur post execution process parent ", 38);
		perror(": ");
		exit(EXIT_FAILURE);
}

// void parent_process(pid_t	child_pid, t_exec *prev_exec_st, t_node *last_node, t_shell *shell)
void parent_process(t_exec *prev_exec_st, t_node *last_node, t_shell *shell)
{
	t_exec	*exec_st_parent;
	pid_t	parent_pid;

	exec_st_parent = init_exec_st_parent(last_node, prev_exec_st); //recup des bon fd 
	parent_pid = fork();
	if (parent_pid < 0)
	{
		perror(": ");
		exit(EXIT_FAILURE); // exit ?
	}
	if (parent_pid == 0)
		parent_fork_process(last_node, prev_exec_st, exec_st_parent, shell);
	close(prev_exec_st->pfd_in);
	close(prev_exec_st->pfd_out);
	free(prev_exec_st);
	free(exec_st_parent);
}