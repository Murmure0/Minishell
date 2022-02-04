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

	i = -1;
	if (sh)
	{
		free(sh->env);
		free(sh->path);
		free(sh);
	}
	if (ps)
	{
		free(ps->prompt);
		while (ps->nodes[++i])
			free(ps->nodes[i]);
		free(ps->nodes);
		free(ps);
	}
	if (n)
	{
		i = -1;
		while (n->cmd[++i])
			free(n->cmd[i]);
		free(n->cmd);
		free(n->infiles->name);
		free(n->infiles);
		free(n->outfiles->name);
		free(n->outfiles);
		free(n);
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
	init_struct(&shell, env);
	while (1)
	{
		parstruct.prompt = readline("minishell$ ");
		add_history(parstruct.prompt);
		nodes = parse(nodes, &parstruct);
		// printf("%s\n", nodes[0].cmd[0]);
		// printf("%s\n", nodes[0].cmd[1]);
		// printf("%s\n", nodes[0].cmd[2]);
		// printf("%s\n", nodes[0].infiles[0].name);
		// printf("%d\n", nodes[0].infiles[0].redir);
		// printf("%s\n", nodes[0].infiles[1].name);
		// printf("%d\n", nodes[0].infiles[1].redir);
		// printf("%s\n", nodes[0].outfiles[0].name);
		// printf("%d\n", nodes[0].outfiles[0].redir);
		// printf("%s\n", nodes[0].outfiles[1].name);
		// printf("%d\n", nodes[0].outfiles[1].redir);
		exec(nodes, shell);
	}
	final_free(&shell, &parstruct, nodes);
	return (0);
}
