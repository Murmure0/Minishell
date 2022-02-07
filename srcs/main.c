#include "../includes/minishell.h"

int	ret_err(int ret, char *msg)
{
	/* exit temporaire en attendant de faire un truc propre avec errno */
	printf("%s\n", msg);
	return (ret);
}

void	final_free(t_shell *sh, t_parsing *ps, t_node *n)
{
	int	i;
	int	j;

	i = -1;
	if (sh)
	{
		free(sh->env);
		free(sh->path);
		free(sh);
	}
	if (n)
	{
		while (++i < ps->pipe_nb + 1)
		{
			j = -1;
			while (n[i].cmd[++j])
				free(n[i].cmd[j]);
			free(n[i].cmd);
			free(n[i].infiles);
			free(n[i].outfiles);
		}
		free(n);
	}
	if (ps)
	{
		free(ps->prompt);
		i = -1;
		while (ps->nodes[++i])
			free(ps->nodes[i]);
		free(ps->nodes);
		free(ps);
	}
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

int main(int argc, char **argv, char **env)
{
	t_parsing	parstruct;
	t_node		*nodes;
	t_shell		shell;

	(void)argc;
	(void)argv;
	init_struct(&shell, env);
	while (1)
	{
		parstruct.prompt = readline("minishell$ ");
		add_history(parstruct.prompt);
		if (not_emptycmd(parstruct.prompt))
		{
			nodes = parse(&parstruct);

				/*		PRINT CMDS		*/

			// int i = -1;
			// while (++i < parstruct.pipe_nb + 1)
			// {
			// 	int j = -1;
			// 	while (nodes[i].cmd[++j])
			// 		printf("Node %d cmd % d : %s\n", i, j, nodes[i].cmd[j]);
			// }

			// 	/*		PRINT INFILES		*/

			// i = -1;
			// while (++i < parstruct.pipe_nb + 1)
			// {
			// 	printf("Node %d infile : %s\n", i, nodes[i].infiles);
			// }

			// // 	/*		PRINT OUTFILES		*/
			
			// i = -1;
			// while (++i < parstruct.pipe_nb + 1)
			// {
			// 	printf("Node %d outfile : %s\n", i, nodes[i].outfiles);
			// }	
			exec(nodes, shell);
		}
	}
	final_free(&shell, &parstruct, nodes);
	return (0);
}
