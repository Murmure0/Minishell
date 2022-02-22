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
		write(2, "Mem. alloc. for execution struct initialisation failed.\n", 57);
		perror(": ");
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

	if(first_node[0].cmd)
	{
		tmp = first_node[0].cmd[0];
		i = -1;
		while (shell->path[++i])
		{
			first_node[0].cmd[0] = ft_strjoin(shell->path[i], tmp);
			if (!tmp)
				return (-1);
			execve(first_node[0].cmd[0], first_node[0].cmd, shell->env);
			free(first_node[0].cmd[0]);
		}
		first_node[0].cmd[0] = tmp;
		execve(first_node->cmd[0], first_node->cmd, shell->env);
	}
	return (0);
}

int	exec_cmd(t_node *first_node, t_shell *shell)
{
	if (!path_finder(first_node, shell))
	{
		//free_all(first_node); fais une bonne fct free stp
		return (-1);
	}
	return (0);
}

/*
void	free_all(t_node *first_node, t_shell shell) // ah ouais ce serait une super idee quand meme
{
	int i = -1;
	while (shell.env[++i])
		free(shell.env[i]);
	i = -1;
	while (shell.path[++i])
		free(shell.path[i]);
	free(shell.env);
	free(shell.path);
	
	i = -1;
	while(first_node[0].cmd[++i])
		free(first_node[0].cmd[i]);
	i = -1;
	while(first_node[0].infiles[++i])
		free(first_node[0].infiles[i]);
	i = -1;
	while(first_node[0].outfiles[++i])
		free(first_node[0].outfiles[i]);
		doit on free egalement les champs name ?
}*/