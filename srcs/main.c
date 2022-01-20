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
	free(shell.path); //boucler dans path et env pour free chaque str allouees
	free(shell.env);
}

int main(int argc, char **argv, char **env)
{
	t_parsing	parstruct;
	t_node		nodes;

	(void)argc;
	(void)argv;
	init_struct(&shell, env); /*fonction qui va initialiser notre structure globale*/
	while (1)
	{
		// ! free prompt
		parstruct.prompt = readline("minishell$ ");
		add_history(parstruct.prompt);
		first_node = parse(&parstruct);
		exec(nodes, shell);
	}
	ft_free(shell);
	return (0);
}