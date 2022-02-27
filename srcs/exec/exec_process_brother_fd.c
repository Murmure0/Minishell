#include "../../includes/minishell.h"

static int	find_fd_in_bro(t_node *middle_node, t_exec *prev_exec_st)
{
	int	fd_in;

	fd_in = 0;
	if (middle_node->infiles || middle_node->infile_hd)
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

static void	pipe_case_bro(t_exec *exec_st_bro)
{
	int	pfd[2];

	if (pipe(pfd) < 0)
		perror(": ");
	exec_st_bro->pfd_out = pfd[1];
	exec_st_bro->pfd_in = pfd[0];
}

static int	find_fd_out_bro(t_node *middle_node, t_exec *exec_st_bro)
{
	int	fd_out;

	fd_out = 1;
	if (exec_st_bro->num_cmd < middle_node->node_nb)
		pipe_case_bro(exec_st_bro);
	if (exec_st_bro->num_cmd < middle_node->node_nb && !middle_node->outfiles)
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
	if (!exec_st_bro)
	{
		write(2, "Memory allocation failed\n", 26);
		perror(": ");
	}
	exec_st_bro->num_cmd = prev_exec_st->num_cmd;
	exec_st_bro->fd_in = find_fd_in_bro(middle_node, prev_exec_st);
	if (exec_st_bro->fd_in < 0)
		return (NULL);
	exec_st_bro->fd_out = find_fd_out_bro(middle_node, exec_st_bro);
	if (exec_st_bro->fd_out < 0)
		return (NULL);
	return (exec_st_bro);
}
