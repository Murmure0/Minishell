#include "../../includes/minishell.h"

int	path_finder_parent(t_node *first_node, t_shell shell)
{
	char	*tmp;
	int		i;

	
		
	if(first_node[0].cmd)
	{
		tmp = first_node[0].cmd[0];
		i = -1;
		while (shell.path[++i])
		{
			first_node[0].cmd[0] = ft_strjoin(shell.path[i], tmp);
			printf("EXEXC cmd : %s\n", first_node[0].cmd[0]); //warning
			if (!tmp)
				return (-1);
			// printf("|%s|\n", first_node[0].cmd[0]);
			execve(first_node[0].cmd[0], first_node[0].cmd, shell.env);
			free(first_node[0].cmd[0]);
		}
		first_node[0].cmd[0] = tmp;
		execve(first_node->cmd[0], first_node->cmd, shell.env);
	}
	return (0);
}

int	exec_cmd_parent(t_node *last_node, t_shell shell)
{
	printf("COMMAND 2eme node : %s\n", last_node->cmd[0]);
	if (!path_finder_parent(last_node, shell))
	{
		//free_all(first_node); faire une bonne fct free
		return (-1);
	}
	return (0);
}

int	find_fd_in_parent(t_node *last_node, t_exec *exec_st)
{
	int	fd_in;

	fd_in = 0;
	if (last_node->infiles)
	{
		fd_in = open(last_node->infiles, O_RDONLY);
		if (fd_in < 0)
		{
			write(2, last_node->infiles, ft_strlen(last_node->infiles));
			perror(": ");
			return (-1);
		}
	}
	else if (exec_st->pfd_in)
		fd_in = exec_st->pfd_in;
	return (fd_in);
}

t_exec	*init_exec_st_parent(t_node *last_node, t_exec *exec_st)
{
	t_exec	*exec_st_parent;

	exec_st_parent = malloc(sizeof(t_exec));
	if (!exec_st_parent)
	{
		write(2, "Memory allocation for last execution struct initialisation failed\n", 67);
		perror(": ");
	}
	exec_st_parent->fd_in = find_fd_in_parent(last_node, exec_st);
	// printf("exec fd in : %d\n",exec_st->fd_in);
	if(exec_st_parent->fd_in < 0)
		return (NULL);


	// exec_st_parent->fd_out = find_fd_out_parent(last_node, exec_st);
	// // printf("exec fd out : %d\n",exec_st->fd_out);
	// if(exec_st_parent->fd_out < 0)
	// 	return (NULL);
	free(exec_st);
	return (exec_st_parent);
}

static void parent_fork_process(t_node *last_node, t_exec *exec_st_parent, t_shell *shell)
{
	// char *tmp;
	// int i;
	if (exec_st_parent->fd_in)
	{
		printf("xxx valeur fdin dans exec st parent : %d\n", exec_st_parent->fd_in);
		//fd_in = open(exec_st_parent->fd_in, O_RDONLY);
		if(dup2(exec_st_parent->fd_in, STDIN_FILENO) < 0)
		{
			write(2, "Dup2 in parent ", 16);
			perror(": ");
			exit(EXIT_FAILURE);
		}
		close(exec_st_parent->fd_in);
	}
	/*close time*/
	// if (!find_builtin(last_node, shell))
	// {
	// 	if(last_node[0].cmd)
	// 	{
	// 		write(1, "debut exec parent\n", 19);
	// 		tmp = last_node[0].cmd[0];
	// 		i = -1;
			
	// 		while (shell->path[++i])
	// 		{
	// 			last_node[0].cmd[0] = ft_strjoin(shell->path[i], tmp);
	// 			printf("EXEC cmd : %s\n", last_node[0].cmd[0]); //warning
	// 			// printf("|%s|\n", last_node[0].cmd[0]);
	// 			execve(last_node[0].cmd[0], last_node[0].cmd, shell->env);
	// 			free(last_node[0].cmd[0]);
	// 		}
	// 		last_node[0].cmd[0] = tmp;
	// 		execve(last_node->cmd[0], last_node->cmd, shell->env);
	// 	}
	if (!find_builtin(last_node, shell))
	{
		exec_cmd_parent(last_node, *shell);
	}





		write(2, "Erreur post execution parent ", 30);
		perror(": ");
	

	//if (exec_st_parent->fd_out)
}

void parent_process(pid_t prev_pid, t_exec *exec_st, t_node *last_node, t_shell *shell)
{
	(void)shell;

	t_exec	*exec_st_parent;
	int		status;
	pid_t	parent_pid;


	status = 0;
	waitpid(prev_pid, &status, 0); //on attend la fin du processus enfant 
	
	printf("infile PFDIN du last node : %d\n", exec_st->pfd_in);
	printf("infile INFILE du last node : %s\n", last_node->infiles);
	
	exec_st_parent = init_exec_st_parent(last_node, exec_st); //recup des bon fd 
	printf("infile INFILE du last node : %d\n", exec_st_parent->fd_in);
	printf("contenu shell path parent : %s\n", shell->path[1]);
	//on lance l'execution dans un fork :
	parent_pid = fork();
	if (parent_pid < 0)
	{
		perror(": ");
		exit(EXIT_FAILURE);
	}
	if (parent_pid == 0)
		parent_fork_process(last_node, exec_st_parent, shell);

	/*close time*/

	waitpid(parent_pid, &status, 0);
	free(exec_st_parent);
}