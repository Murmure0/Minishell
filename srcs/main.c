#include "../includes/minishell.h"

int	ret_err(int ret, char *msg)
{
	if (!msg)
		perror(PERR);
	else
		printf("%s\n", msg);
	return (ret);
}

void	ft_exit(t_shell *sh, t_parsing *ps, t_node *n, char *err)
{
	if (err)
		write(2, err, ft_strlen(err));
	final_free(sh, ps, n);
	exit(EXIT_FAILURE);
}

int not_emptycmd(char *cmd)
{
	int i;

	i = -1;
	if (cmd == NULL)
		return (1);
	while (cmd[++i])
	{
		if (!is_space(cmd[i]))
			return (1);
	}
	return (0);
}

static void print_debug(t_parsing parstruct, t_node *nodes, t_shell shell)
{
	(void)shell;
	/*		PRINT CMDS		*/

	int i = -1;
	while (++i < parstruct.pipe_nb + 1)
	{
		int j = -1;
		if (nodes[i].cmd)
			while (nodes[i].cmd[++j])
				printf("Node %d cmd % d : |%s|\n", i, j, nodes[i].cmd[j]);
	}

		/*		PRINT INFILES		*/

	i = -1;
	while (++i < parstruct.pipe_nb + 1)
	{
		printf("Node %d infile : |%s|\n", i, nodes[i].infiles);
	}

	// 	/*		PRINT OUTFILES		*/
	
	i = -1;
	while (++i < parstruct.pipe_nb + 1)
	{
		printf("Node %d outfile : |%s|\n", i, nodes[i].outfiles);
	}
}

int main(int argc, char **argv, char **env)
{
	t_parsing	parstruct;
	t_node		*nodes;
	t_shell		shell;

	(void)argc;
	(void)argv;
	nodes = NULL;
	init_shell_struct(&shell, env); //faire un check sur le shell pendant l'init
	tcgetattr(STDIN_FILENO, &shell.termios_p); //permet d'avoir le status de l'affichage au debut, pour le reinitialiser apres l'eventuelle utilisation de top qui fout la merde
	while (1)
	{
		signal(SIGINT, handle_signal);
		signal(SIGQUIT, SIG_IGN);
		parstruct.prompt = readline("minishell$ ");
		add_history(parstruct.prompt);
		if (not_emptycmd(parstruct.prompt))
		{
			nodes = parse(&parstruct, &shell);
			if (parstruct.stop_err)
				continue ;
			print_debug(parstruct, nodes, shell);
			if (nodes)
			{
				exec(nodes, &shell);
				free_nodestruct(nodes);
				free_parstruct(&parstruct);
			}
		}
		else
		{
			parstruct.prompt = NULL;
			free(parstruct.prompt);
		}
	}
	write(2,"sortie exec\n", 13);
	free_shellstruct(&shell);
	
	return (0);
}

/* TESTS QUI LEAKS (sans exec)
	$< >

*/
