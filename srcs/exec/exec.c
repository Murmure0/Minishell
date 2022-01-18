#include "../../includes/minishell.h"
/*
char	*ft_strdup(char *src)
{
	char	*string;
	int		src_size;
	int		i;

	if (!src)
		return (NULL);
	i = 0;
	src_size = ft_strlen(src);
	string = malloc(sizeof(char) * (src_size + 1));
	if (!string)
		return (NULL);
	while (i < src_size)
	{
		string[i] = src[i];
		i++;
	}
	string[src_size] = '\0';
	return (string);
}

int	ft_strlen(const char *str)
{
	int	count;

	count = 0;
	if (!str)
		return (0);
	while (str[count] != '\0')
		count++;
	return (count);
}

------------*/

int find_fd_in(t_node node)
{
	int fd_in;

	fd_in = 0;
	while (node.infiles)
	{
		if (node.infiles->redir == 1)
		{
			fd_in = open(node.infiles->name, O_RDONLY);
			printf("nom infile : %s\n", node.infiles->name);
			printf("|%d|\n", fd_in);
			if (fd_in < 0)
			{
				write(2, node.infiles->name, ft_strlen(node.infiles->name));
				perror(": ");
				exit (errno);
			}
			if (node.infiles->next)
			{
				printf("close %s\n", node.infiles->name);
				close(fd_in);
			}
			node.infiles = node.infiles->next;
		}
	}
	return (fd_in);
}

/*----------*/

static char	**recup_path(char **env)
{
	int		i;
	char	*path_line;
	char	**path_tab;

	i = -1;
	while (env[++i])
	{
		if (!ft_strncmp("PATH=", env[i], 5))
		{
			path_line = ft_substr(env[i], 5, (my_strlen(env[i]) - 5));
			if (!path_line)
				return (NULL);
			path_tab = ft_split(path_line, ':', 1);
			if (!path_tab)
				return (NULL);
		}
	}
	return (path_tab);
}

static char	**recup_cmd(char *str)
{
	char	**cmd_tab;
	char	*cmd;
	int		z;

	z = 0;
	if (!str || !*str || str[0] == ' ')
		return (NULL);
	cmd = ft_strdup(str);
	cmd_tab = ft_split(cmd, ' ', 0);
	if (!cmd_tab)
	{
		free(cmd);
		return (NULL);
	}
	while (cmd_tab[z])
	{
		if (cmd_tab[z][my_strlen(cmd_tab[z]) - 1] == ' ')
			cmd_tab[z][my_strlen(cmd_tab[z]) - 1] = '\0';
		z++;
	}
	free(cmd);
	return (cmd_tab);
}

static int	path_finder(char **cmd_tab, char **path_tab, char **env)
{
	char	*tmp;
	int		i;

	i = -1;
	tmp = cmd_tab[0];
	while (path_tab[++i])
	{
		cmd_tab[0] = ft_strjoin(path_tab[i], tmp);
		if (!cmd_tab[0])
			return (-1);
		execve(cmd_tab[0], cmd_tab, env);
		free(cmd_tab[0]);
	}
	cmd_tab[0] = tmp;
	execve(cmd_tab[0], cmd_tab, env);
	free(tmp);
	return (0);
}

static void	free_all(char **path_tab, char **cmd_tab, int z)
{
	int	i;

	i = -1;
	while (path_tab[++i])
		free(path_tab[i]);
	free(path_tab);
	if (z == 1)
	{
		i = 0;
		while (cmd_tab[++i])
			free(cmd_tab[i]);
		free(cmd_tab);
	}
}

int	exec_cmd(t_node node, char **env)
{
	char	**path_tab;
	char	**cmd_tab;

	path_tab = recup_path(env);
	if (!path_tab)
		return (-1);
	cmd_tab = recup_cmd(av);
	if (!cmd_tab)
	{
		free_all(path_tab, cmd_tab, 0);
		write(2, "Error : invalid command.", 24);
		return (-1);
	}
	if (!path_finder(cmd_tab, path_tab, env))
	{
		free_all(path_tab, cmd_tab, 1);
		write(2, "Error : invalid command.", 24);
		return (-1);
	}
	free_all(path_tab, cmd_tab, 1);
	return (0);
}


/*----------*/

void child_process(pid_t child_pid, int fd_in, t_node node, char **env/*, int *fds*/)
{
	if (child_pid == 0)
	{
		if (fd_in > 0)
		{
			if (dup2(fd_in, STDIN_FILENO) < 0)
			{
			perror(": ");
			exit (errno);
			}
		}
		/*if (dup2(fds[1], STDOUT_FILENO) < 0)
			error_message(7);*/
		close(fd_in);
		/*close(fds[0]);
		close(fds[1]);*/
		exec_cmd(node, env);
		close(STDOUT_FILENO);
		ft_exit();
	}
}

int exec(t_node node)
{
	
	int fd_in;
	pid_t child_pid;
	int		status;

	fd_in = find_fd_in(node);
	status = 0;
	printf("valeur fd_in : %d\n",fd_in);
	child_pid = fork();
	if (child_pid < 0)
	{
		write(2, "Child fork failed", 18);
		perror(": ");
		exit (errno);
	}
	child_process(child_pid, fd_in, node, env /*,fds*/);
	waitpid(-1, &status, 0);
	//parcourir la lst_cmd.infile : verification qu'il y a du contenu (erreur); si un fd ne peut pas etre ouvert on quitte
	// o/c chaque infile tant qu'il y a un next;
	//verifier le type de redirection : 
	// si < : on ouvre juste le fichier
	// si << : recuparation here_doc.c en changeant des tas de truc
	//on conserve le fd du dernier dans fd_in;
	


	//parcourir la lst_cmd.outfile : 
	// - pas de contenu : s'il y a un lst_cmd.next c'est qu'il y a un pipe, on ecrit le resultat de la cmd dans fds[1]
	//						pas de lst_cmd.next : dup sur stdout
	// - o/c chaque infile tant qu'il y a un next;
	// 	conserver le fd du dernier dans un ft_out


	//verifier s'il y a du contenu dans lst_cmd


	//si pas de lst_cmd.next : pas de pipe, pas de cmd suivante 
	// OU si built-in (comparer le contenu de lst_cmd.cmd a la liste des built-in)
	//
	//dup2 les entree et sorties
	//close
	//execution de la commande sans fork


	//si lst_cmd.next : il y a un pipe
	//dup2 
	return (0);
}

/*-----main-------

	int main(int ac, char **av, char **env)
	{
		t_node node;

		char *str1 = {"infile_1"};
		char *str2 = {"infile_2"};
		char *str3 = {"outfile_1"};
		char *str4 = {"outfile_2"};
		char *str5 = {"echo"};
		char *str6 = {"hello"};

		t_token in1, in2, out1, out2, cmd1, cmd2;

		//lst chainee infile
		in1.redir = 0;
		in1.name = ft_strdup(str1);

		in2.redir = 0;
		in2.name = ft_strdup(str2);

		in1.next = &in2;
		in2.next = NULL;

		lst chainee outfile
		out1.redir = 0;
		out1.name = ft_strdup(str3);

		out2.redir = 1;
		out2.name = ft_strdup(str4);
		out1.next = &out2;
		out2.next = NULL;

		lst chainee cmd
		cmd1.redir = 0;
		cmd1.name = ft_strdup(str5);
		cmd1.next = &cmd2;

		cmd2.redir = 0;
		cmd2.name = ft_strdup(str6);
		cmd2.next = NULL;


		node.infiles = &in1;
		node.outfiles = &out1;
		node.cmd = &cmd1;

		node.env = env;
		node.next = NULL;


		exec(node, env);
		return (0);
	}
*/