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
		return (NULL);
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
	char	*cmd;
	int		i;

	i = -1;
	if (first_node[0].cmd)
	{
		while (shell->path[++i])
		{
			cmd = ft_strjoin(shell->path[i], first_node[0].cmd[0]);
			if (!cmd)
				return (-1);
			execve(cmd, first_node[0].cmd, shell->env);
			free(cmd);
		}
		write(2, "minishell: ", 12);
		write(2, first_node[0].cmd[0], ft_strlen(first_node[0].cmd[0]));
		write(2, ": command not found\n", 21);
		exit(EXIT_FAILURE);
	}
	return (0);
}

int	exec_cmd(t_node *first_node, t_shell *shell)
{
	if (!path_finder(first_node, shell))
		return (-1);
	return (0);
}
