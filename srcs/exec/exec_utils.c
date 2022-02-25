#include "../../includes/minishell.h"

void	fd_dup(int fd, int std)
{
	if (dup2(fd, std) < 0)
	{
		close(fd);
		perror(": ");
		exit (errno);
	}
	close(fd);
}

t_exec	*init_exec_st(t_node *first_node)
{
	t_exec	*exec_st;

	exec_st = malloc(sizeof(t_exec));
	if (!exec_st)
	{
		write(2, "Memory allocation failed.\n", 57);
		perror(": ");
		return (NULL);
	}
	exec_st->num_cmd = 1;
	exec_st->pfd_in = 0;
	exec_st->pfd_out = 0;
	exec_st->fd_in = find_fd_in(first_node);
	if (exec_st->fd_in < 0)
		return (NULL);
	exec_st->fd_out = find_fd_out(first_node, exec_st);
	if (exec_st->fd_out < 0)
		return (NULL);
	return (exec_st);
}

int	path_finder(t_node *first_node, t_shell *shell)
{
	char	*tmp;
	int		i;

	if (first_node[0].cmd)
	{
		execve(first_node->cmd[0], first_node->cmd, shell->env);
		i = -1;
		tmp = ft_strdup(first_node[0].cmd[0]);
		while (shell->path[++i])
		{
			first_node[0].cmd[0] = ft_strjoin(shell->path[i], tmp);
			if (!tmp)
				return (-1);
			execve(first_node[0].cmd[0], first_node[0].cmd, shell->env);
			free(first_node[0].cmd[0]);
		}
		free(tmp);
	}
	return (0);
}

int	exec_cmd(t_node *first_node, t_shell *shell)
{
	if (!path_finder(first_node, shell))
		return (-1);
	return (0);
}
