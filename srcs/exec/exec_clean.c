#include "../../includes/minishell.h"

static int	path_finder(t_node *first_node)
{
	char	*tmp;
	int		i;

	i = -1;
	tmp = first_node->cmd[0];
	while (g_shell.path[++i])
	{
		first_node->cmd[0] = ft_strjoin(g_shell.path[i], tmp);
		// printf("path+cmd = |%s| next = |%s|\n", first_node->cmd[0], first_node->cmd[1]);
		if (!first_node->cmd[0])
			return (-1);
		execve(first_node->cmd[0], first_node->cmd, g_shell.env);
		free(first_node->cmd[0]);
	}
	first_node->cmd[0] = tmp;
	execve(first_node->cmd[0], first_node->cmd, g_shell.env);
	free(tmp);
	return (0);
}

void	free_all(t_node *first_node)
{
	int i = -1;
	while (g_shell.env[++i])
		free(g_shell.env[i]);
	i = -1;
	while (g_shell.path[++i])
		free(g_shell.path[i]);
	i = -1;
	while(first_node->cmd[++i])
		free(first_node->cmd[i]);
	//fct qui free les lst infile et outfile
}

int	exec_cmd(t_node *first_node)
{
	if (!path_finder(first_node))
	{
		//free_all(first_node);
		return (-1);
	}
	//free_all(first_node);
	return (0);
}

void child_process(pid_t child_pid/*, int fd_in*/, t_node *first_node/*, int *fds*/)
{
	if (child_pid == 0)
	{
		/*if (fd_in > 0)
		{
			if (dup2(fd_in, STDIN_FILENO) < 0)
			{
			perror(": ");
			exit (errno);
			}
		}*/
		/*if (dup2(fds[1], STDOUT_FILENO) < 0)
			error_message(7);
		close(fds[0]);
		close(fds[1]);*/
		//close(fd_in);
		exec_cmd(first_node);
		//write(2, &first_node->cmd[0], ft_strlen(first_node->cmd[0]));
		write(2, "Erreur post execution", 22);
		perror(": ");
		//close(STDOUT_FILENO);
		ft_exit();
	}
}


int exec(t_node *first_node)
{
	
	//int		fd_in;
	pid_t	child_pid;
	int		status;

	//fd_in = 0;
	//fd_in = find_fd_in(first_node);
	//printf("valeur fd_in : %d\n",fd_in);
	// printf("contenu |%s|\n", first_node->cmd[0]);
	status = 0;
	child_pid = fork();
	if (child_pid < 0)
	{
		write(2, "Child fork failed", 18);
		perror(": ");
		exit (errno);
	}
	child_process(child_pid/*, fd_in,*/, first_node/*,fds*/);
	waitpid(-1, &status, 0);
	return(0);
}