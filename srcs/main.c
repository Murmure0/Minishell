#include "../includes/minishell.h"

int	g_exit_st;

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
	(void)sh;
	(void)ps;
	(void)n;
	if (err)
		write(2, err, ft_strlen(err));
	exit(EXIT_FAILURE);
}

static int	not_emptycmd(char *cmd)
{
	int	i;

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

void	add_spaces(t_parsing *ps)
{
	int	i;
	char	*tmp;

	i = -1;
	tmp = ft_strdup(ps->prompt);
	if (!tmp)
		exit(EXIT_FAILURE);
	free(ps->prompt);
	ps->prompt = malloc(sizeof(char) * ft_strlen(tmp) + 3);
	if (!ps->prompt)
		exit(EXIT_FAILURE);
	ps->prompt[0] = ' ';
	while (tmp && tmp[++i])
	{
		ps->prompt[i + 1] = tmp[i];
	}
	free(tmp);
	ps->prompt[i + 1] = ' ';
	ps->prompt[i + 2] = 0;
}

static void	process_readline(t_parsing *parstruct, t_node *nodes, t_shell *shell)
{
	char	*tmp;

	tmp = str_slice(parstruct->prompt, 1, ft_strlen(parstruct->prompt) - 1);
	if (!tmp)
		exit(EXIT_FAILURE);
	add_history(tmp);
	free(tmp);
	if (not_emptycmd(parstruct->prompt))
	{
		nodes = parse(parstruct, shell);
		if (parstruct->stop_err)
		{
			final_free(NULL, parstruct, nodes);
			return ;
		}
		print_debug(*parstruct, nodes, *shell);
		free_parstruct(parstruct);
		if (nodes)
		{
			exec(nodes, shell);
			free_nodestruct(nodes);
		}
	}
	else
	{
		free(parstruct->prompt);
		parstruct->prompt = NULL;
	}
}

int	main(int argc, char **argv, char **env)
{
	t_parsing	parstruct;
	t_node		*nodes;
	t_shell		shell;

	(void)argc;
	(void)argv;
	nodes = NULL;
	g_exit_st = 0;
	init_shell_struct(&shell, env);
	tcgetattr(STDIN_FILENO, &shell.termios_p);
	while (1)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, handle_signal);
		parstruct.prompt = readline("minishell$ ");
		if (!parstruct.prompt)
		{
			write(1, "exit\n", 5);
			break ;
		}
		add_spaces(&parstruct);
		process_readline(&parstruct, nodes, &shell);
	}
	free_shellstruct(&shell);
	return (g_exit_st);
}

//  echo ""
//  echo "a|b"