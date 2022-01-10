/*-----------Nos strutures------------*/

struct s_file
{
	int double_chevron;
	char *name;
}

struct s_command
{
	struct s_file *infiles;
	struct s_file *outfiles;
	char **cmd;
	char **env;
	struct s_command *next;
}

/*----------Pour l'execution----------*/

executer_commande(struct s_command *command)
{
	fait execve et les redirections
	return pipe; (vide si outfile)
}

executer_tout(struct s_command *command)
{
	struct s_command tmp = command;
	while (tmp)
	{
		fd = executer_commande;
		tmp = tmp->next;
	}
}
