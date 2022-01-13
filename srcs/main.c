#include "../includes/minishell.h"


int main(int argc, char **argv, char **env)
{
	t_command lst_cmd;

	init_struct(&g_struct, env); /*fonction qui va initialiser notre structure globale*/

	exec(g_struct, lst_cmd);
	return (0);
}
