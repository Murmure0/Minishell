#include "../../includes/minishell.h"

static int	path_finder(t_node *first_node, t_shell shell)
{
	char	*tmp;
	int		i;

	i = -1;
	while (shell.path[++i])
	{
		tmp = ft_strjoin(shell.path[i], first_node[0].cmd[0]);
		//printf("path+cmd = |%s| next = |%s|\n", first_node->cmd[0], first_node->cmd[1]);
		//printf("shell.env : |%s|\n", shell.env[i]);
		if (!tmp)
			return (-1);
		execve(tmp, first_node->cmd, shell.env);
		free(tmp);
	}
	// first_node[0].cmd = tmp;
	//execve(first_node->cmd[0], first_node->cmd, shell.env);
	// free(tmp);
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

int exec(t_node *first_node, t_shell shell)
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
	// if (child_pid == 0)
	// {
	// 	exec_cmd(first_node);
	// 	perror(": ");
	// 	exit(EXIT_FAILURE);
	// }
	if (child_pid == 0)
		child_process(child_pid/*, fd_in,*/, first_node/*,fds*/, shell);
	else
		waitpid(child_pid, &status, 0);
	return(0);
}

// int main(int argc, char **argv, char **env)
// {
// 	//Initialisation de la struct nodes

// 	/*char     input[50] = {"< infile cat -e | ls > output"};*/
//     t_node     *nodes;
// 	t_shell		shell;
// 	t_parsing	parstruct;

//     nodes = malloc(sizeof(t_token) * 2);
    
// /*     1er node = "< infile cat"    */
// /*     infiles du 1er node :         */
//     nodes[0].infiles = malloc(sizeof(t_token) * 1);
//     nodes[0].infiles[0].name = ft_strdup("infile");
//     nodes[0].infiles[0].redir = 1;
//     nodes[0].infiles[0].pos = 2;

// /*     cmd du 1er node :         */
//     nodes[0].cmd = malloc(sizeof(t_token) * 2);
//     nodes[0].cmd = ft_strdup("cat");
//     nodes[0].cmd[0].redir = 0;
//     nodes[0].cmd[0].pos = 9;
    
// /*     argument de cmd du 1er node :         */
//     nodes[0].cmd[1].name = ft_strdup("-e");
//     nodes[0].cmd[1].redir = 0;
//     nodes[0].cmd[1].pos = 13;

// /*     2e node = "ls > output"    */
// /*     cmd du 2e node :         */
//     nodes[1].cmd = malloc(sizeof(t_token) * 1);
//     nodes[1].cmd = ft_strdup("ls");
//     nodes[1].cmd[0].redir = 0;
//     nodes[1].cmd[0].pos = 18;

// /*     outfiles du 2e node :         */
//     nodes[1].outfiles = malloc(sizeof(t_token) * 1);
//     nodes[1].outfiles[0].name = ft_strdup("output");
//     nodes[1].outfiles[0].redir = 2;
//     nodes[1].outfiles[0].pos = 23;

//     printf("%s\n", nodes[0].infiles[0].name);
//     printf("%s\n", nodes[0].cmd);
//     printf("%s\n", nodes[0].cmd[1].name);
// 	//

// 	init_struct(&shell, env); /*fonction qui va initialiser notre structure globale*/
// 	while (1)
// 	{
// 		// ! free prompt
// 		parstruct.prompt = readline("minishell$ ");
// 		add_history(parstruct.prompt);
// 		exec(nodes, shell);
// 	}
// 	ft_free(shell);
// 	return (0);
// }