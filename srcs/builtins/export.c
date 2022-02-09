#include "../../includes/minishell.h"

int	my_export(t_shell *sh, char **cmd)
{
	int	cmd_pos;
	
	// ne doit pas export mais update si on a déjà une key
	// if wrong key, n'export pas mais ne renvoit pas d'err
	cmd_pos = 0;
	while (cmd[++cmd_pos])
	{
		printf("adding %s\n", cmd[cmd_pos]);
		sh->env = update_env_key(sh->env, NULL, cmd[cmd_pos]);
	}
	cmd_pos = -1;
	while (sh->env[++cmd_pos])
		printf("%s\n", sh->env[cmd_pos]);
	return (0);
}