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
	free(g_shell.path);
	free(g_shell.env);
}

int main(int argc, char **argv, char **env)
{
	// t_command lst_cmd;
	t_parsing	parstruct;
	t_node	*first_node; //

	(void)argc;
	(void)argv;
	init_struct(&g_shell, env); /*fonction qui va initialiser notre structure globale*/
	while (1)
	{
		// ! free prompt
		parstruct.prompt = readline("minishell$ ");
		add_history(parstruct.prompt);
		//first_node = parse(&parstruct);
		first_node = parse(&parstruct);
		// printf("recup first node : |%s|\n", first_node->cmd[0]);
		// printf("recup first node : |%s|\n", first_node->cmd[1]);
		// printf("recup first node : |%s|\n", first_node->cmd[2]);
		// printf("recup first node : |%s|\n", first_node->cmd[3]);
		exec(first_node);
	}
	ft_free();
	return (0);
}