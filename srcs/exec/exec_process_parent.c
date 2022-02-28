#include "../../includes/minishell.h"

int	find_fd_in_parent(t_node *last_node, t_exec *exec_st)
{
	int	fd_in;

	fd_in = 0;
	if (last_node->infiles || last_node->infile_hd)
	{
		if (last_node->infiles && last_node->in_id == 2)
		{
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
	// return if !exec_st_parent
	exec_st_parent->pfd_in = 0;
	exec_st_parent->pfd_out = 0;
	if (!exec_st_parent)
	{
		write(2, "Memory allocation failed\n", 26);
		perror(": ");
	}
	exec_st_parent->fd_in = find_fd_in_parent(last_node, exec_st);
	if (exec_st_parent->fd_in < 0)
		return (NULL);
	exec_st_parent->fd_out = find_fd_out_parent(last_node);
	if (exec_st_parent->fd_out < 0)
		return (NULL);
	return (exec_st_parent);
}

static void	parent_fork_process(t_node *last_node, t_exec *exec_st,
	t_exec *exec_st_parent, t_shell *shell)
{
	if (exec_st_parent->fd_in > 0)
		fd_dup(exec_st_parent->fd_in, STDIN_FILENO);
	if (exec_st_parent->fd_out > 1)
		fd_dup(exec_st_parent->fd_out, STDOUT_FILENO);
	close(exec_st->pfd_in);
	close(exec_st->pfd_out);
	free(exec_st);
	free(exec_st_parent);
	if (!find_builtin(last_node, shell, 'y'))
	{
		exec_cmd(last_node, shell);
		write(2, "Erreur post execution process parent ", 38);
		perror(": ");
		exit(EXIT_FAILURE);
	}
}

void	parent_process(t_exec *prev_exec_st, t_node *last_node, t_shell *shell)
{
	t_exec	*exec_st_parent;
	pid_t	parent_pid;

	exec_st_parent = init_exec_st_parent(last_node, prev_exec_st);
	// return err if malloc failed
	parent_pid = fork();
	if (parent_pid < 0)
	{
		write(2, "Parent fork failed", 19);
		perror(": ");
		free(prev_exec_st);
		free(exec_st_parent);
		exit(EXIT_FAILURE);
	}
	if (parent_pid == 0)
		parent_fork_process(last_node, prev_exec_st, exec_st_parent, shell);
	close(prev_exec_st->pfd_in);
	close(prev_exec_st->pfd_out);
	free(prev_exec_st);
	free(exec_st_parent);
}
