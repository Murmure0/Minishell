#include "../includes/minishell.h"

void	ft_exit(void)
{
	ft_free();
	/* exit temporaire en attendant de faire un truc propre avec errno */
	exit(EXIT_FAILURE);
}

void	ft_free(void)
{
	/* reflechir sur quel check faire pour eviter les free non mallocs */
	// free(g_shell.path);
	// free(g_shell.env);
}

int main(int argc, char **argv, char **env)
{
	t_parsing	parstruct;
	t_node		*nodes;
	t_shell		shell;

	(void)argc;
	(void)argv;
	nodes = malloc(sizeof(t_node) * 100);
	nodes[0].infiles[0].name = ft_strdup("infile");
	init_struct(&shell, env); /*fonction qui va initialiser notre structure globale*/
	while (1)
	{
		// ! free prompt
		parstruct.prompt = readline("minishell$ ");
		add_history(parstruct.prompt);
		// parse(&nodes, &parstruct);
		// exec(nodes);
	}
	ft_free();
	return (0);
}