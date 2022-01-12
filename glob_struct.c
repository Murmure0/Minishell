/*-----------Nos strutures------------*/

struct s_file
{
	int double_chevron;
	char *name;
	struct s_file *next;
}

struct s_command
{
	struct s_file *infiles; //tout les infile precedents la cmd sont stockés la dedans dans 
	struct s_file *outfiles; // tous les outfile suivant la cmd 
	char **cmd; //la cmd du pipe actuel
	char **env;
	struct s_command *next; // la commande du prochain pipe
} t_command

//Une commande = un chainon qui contient des lst chainees des infiles et des outfiles
//on arrive sur le premier chainon : on check le premier infile 
// si simple chevron : ouverture fd (check si retour est < 0), s'il y a un next : on close le fd et on passe au chainon suivant
// s'il n'y a pas de next : on renvoie le fd pour la cmd 

//on check les outfile de la meme maniere, le dernier voit son fd envoyé a la cmd

//on lie les fd a l'entree et la sortie de la cmd

//on execute la cmd

//on check s'il y a une cmd suivante avec le *next : si rien : fini !

//sinon : si on a un infile, le resultat de la cmd precedente est perdu car c'est son fd qui sera lié a l'entree de la cmd
//s'il n'y a pas d'infile, on recupere bien le fd de l'outfile de la cmd prec
//s'il y a un outfile on redirige la sortie de la cmd vers celui ci

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
