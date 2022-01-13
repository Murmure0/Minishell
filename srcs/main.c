#include "../includes/minishell.h"

void	ft_exit(void)
{
	ft_free();
	exit(EXIT_FAILURE);
}

void	ft_free(void)
{
	/* reflechir sur quel check faire pour eviter les free non mallocs */
	free(g_shell.path);
	free(g_shell.env);
	free(g_shell.prompt);
}

int main(int argc, char **argv, char **env)
{
	t_command lst_cmd;

	init_struct(&g_shell, env); /*fonction qui va initialiser notre structure globale*/
	while (1)
	{
		g_shell.prompt = readline("minishell$ ");
		parse();
		exec(g_shell, lst_cmd);
	}
	ft_free();
	return (0);
}