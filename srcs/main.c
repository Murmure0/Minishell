#include "../includes/minishell.h"

void	ft_exit(t_shell shell)
{
	ft_free(shell);
	/* exit temporaire en attendant de faire un truc propre avec errno */
	exit(EXIT_FAILURE);
}

void	ft_free(t_shell shell)
{
	/* reflechir sur quel check faire pour eviter les free non mallocs */
	// free(g_shell.path);
	// free(g_shell.env);
	printf("i'm freeeee\n");
}

int main(int argc, char **argv, char **env)
{
	t_parsing	parstruct;
	t_node		*nodes;
	t_shell		g_shell;

	(void)argc;
	(void)argv;
	init_struct(&g_shell, env); /*fonction qui va initialiser notre structure globale*/
	while (1)
	{
		// ! free prompt
		parstruct.prompt = readline("minishell$ ");
		add_history(parstruct.prompt);
		nodes = parse(nodes, &parstruct);
		printf("command %s\n", nodes[0].cmd[0]);
		exec(nodes, g_shell);
	}
	ft_free(g_shell);
	return (0);
}