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
	//A VIRER

	/*char     input[50] = {"< infile cat -e | ls > output"};*/
    t_node     *nodes;

    nodes = malloc(sizeof(t_token) * 2);
    
/*     1er node = "< infile cat"    */
/*     infiles du 1er node :         */
    nodes[0].infiles = malloc(sizeof(t_token) * 1);
    nodes[0].infiles[0].name = ft_strdup("infile");
    nodes[0].infiles[0].redir = 1;
    nodes[0].infiles[0].pos = 2;

/*     cmd du 1er node :         */
    nodes[0].cmd = malloc(sizeof(t_token) * 2);
    nodes[0].cmd[0].name = ft_strdup("cat");
    nodes[0].cmd[0].redir = 0;
    nodes[0].cmd[0].pos = 9;
    
/*     argument de cmd du 1er node :         */
    nodes[0].cmd[1].name = ft_strdup("-e");
    nodes[0].cmd[1].redir = 0;
    nodes[0].cmd[1].pos = 13;

/*     2e node = "ls > output"    */
/*     cmd du 2e node :         */
    nodes[1].cmd = malloc(sizeof(t_token) * 1);
    nodes[1].cmd[0].name = ft_strdup("ls");
    nodes[1].cmd[0].redir = 0;
    nodes[1].cmd[0].pos = 18;

/*     outfiles du 2e node :         */
    nodes[1].outfiles = malloc(sizeof(t_token) * 1);
    nodes[1].outfiles[0].name = ft_strdup("output");
    nodes[1].outfiles[0].redir = 2;
    nodes[1].outfiles[0].pos = 23;

    printf("%s\n", nodes[0].infiles[0].name);
    printf("%s\n", nodes[0].cmd[0].name);
    printf("%s\n", nodes[0].cmd[1].name);
	//

	// t_command lst_cmd;
	t_parsing	parstruct;
	t_node	*first_node; //
	t_shell shell;

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