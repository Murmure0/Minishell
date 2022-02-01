#include "../../includes/minishell.h"

static int	path_finder(t_node *first_node, t_shell shell)
{
	char	*tmp;
	int		i;

	tmp = first_node[0].cmd[0]; //dup ?
	i = -1;
	while (shell.path[++i])
	{
		first_node[0].cmd[0] = ft_strjoin(shell.path[i], tmp);
		if (!tmp)
			return (-1);
		execve(first_node[0].cmd[0], first_node->cmd, shell.env);
		free(first_node[0].cmd[0]);
	}
	first_node[0].cmd[0] = tmp; //dupdup ?
	execve(first_node->cmd[0], first_node->cmd, shell.env);
	free(tmp);
	return (0);
}

void	free_all(t_node *first_node, t_shell shell)
{
	int i = -1;
	(void)first_node;
	while (shell.env[++i])
		free(shell.env[i]);
	i = -1;
	while (shell.path[++i])
		free(shell.path[i]);
	i = -1;
	/*while(first_node[0].cmd[++i].name)
		free(first_node[0].cmd[i].name);*/
	//fct qui free les lst infile et outfile
}

int	exec_cmd(t_node *first_node, t_shell shell)
{
	if (!path_finder(first_node, shell))
	{
		//free_all(first_node);
		return (-1);
	}
	//free_all(first_node);
	return (0);
}

void child_process(pid_t child_pid/*, int fd_in*/, t_node *first_node/*, int *fds*/, t_shell shell)
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
		}
		if (dup2(fds[1], STDOUT_FILENO) < 0)
			error_message(7);
		close(fds[0]);
		close(fds[1]);
		//close(fd_in);*/
		exec_cmd(first_node, shell);
		//write(2, &first_node->cmd[0], ft_strlen(first_node->cmd[0]));
		write(2, "Erreur post execution", 22);
		perror(": ");
		//close(STDOUT_FILENO);
		exit (errno);
	}
}

int	find_fd_in(t_node *first_node)
{
	int	fd_in;
	int	i;

	i = -1;
	fd_in = 0;
	if (!first_node[0].infiles[0].name)
		return (fd_in);
	while (first_node[0].infiles[++i].name)
	{
		// printf("FIND IN\n");
		// printf("valeur de i : %d\n", i);
		fd_in = open(first_node[0].infiles[i].name, O_RDONLY);
		// printf("ouverture : %s\n",first_node[0].infiles[i].name);
		if (fd_in < 0)
			return (-1);
		if (first_node[0].infiles[i + 1].name != NULL)
		{
			// printf("fermeture : %s\n",first_node[0].infiles[i].name);
			close(fd_in);
		}
		// printf("valeur de i : %d\n", i);
	}
	return (fd_in);
}

int exec(t_node *first_node, t_shell shell)
{
	
	int		fd_in;
	pid_t	child_pid;
	int		status;
	// t_exec *exec_st;

	// exec_st = malloc(sizeof(t_exec));
	// exec_st->fd_in = find_fd_in(first_node);
	// printf("contenu |%s|\n", first_node->cmd[0]);
	fd_in = find_fd_in(first_node);
	// printf("contenu name infile1 |%s|\n", first_node->infiles[0].name);
	// printf("contenu name infile2 |%s|\n", first_node->infiles[1].name);
	// printf("resultat fd_in : |%d|\n", fd_in);
	status = 0;
	child_pid = fork();
	if (child_pid < 0)
	{
		write(2, "Child fork failed", 18);
		perror(": ");
		exit (errno);
	}
	if (child_pid == 0)
		child_process(child_pid,/* fd_in,*/ first_node, /*,fds*/ shell);
	else
		waitpid(child_pid, &status, 0);
	return(0);
}
