#include "../../includes/minishell.h"

int exec(t_command lst_cmd)
{
	int fd_in;
	// int fd_out;
	
	//parcourir la lst_cmd.infile : verification qu'il y a du contenu (erreur); si un fd ne peut pas etre ouvert on quitte
	// o/c chaque infile tant qu'il y a un next;
	//verifier le type de redirection : 
	// si < : on ouvre juste le fichier
	// si << : recuparation here_doc.c en changeant des tas de truc
	//on conserve le fd du dernier dans fd_in;
	while (lst_cmd.infiles->next)
	{
		if (lst_cmd.infiles->double_chevron == 1)
		{
			fd_in = open(lst_cmd.infiles->name, O_RDONLY);
			if (fd_in < 0)
			{
				if (errno == ENOENT)
				{
					write(2, &lst_cmd.infiles->name, ft_strlen(lst_cmd.infiles->name));
					perror(": ");
					//write(2, ": Permission denied", 20);
				}
				else if (errno == EACCES)
				{
					write(2, &lst_cmd.infiles->name, ft_strlen(lst_cmd.infiles->name));
					perror(": ");
					//write(2, ": No such file or directory", 28);
				}
				exit (errno);
			}
		}
	}

	return (0);
	//parcourir la lst_cmd.outfile : 
	// - pas de contenu : s'il y a un lst_cmd.next c'est qu'il y a un pipe, on ecrit le resultat de la cmd dans fds[1]
	//						pas de lst_cmd.next : dup sur stdout
	// - o/c chaque infile tant qu'il y a un next;
	// 	conserver le fd du dernier dans un ft_out


	//verifier s'il y a du contenu dans lst_cmd
	if(!lst_cmd.cmd)
		exit(EXIT_SUCCESS);


	//si pas de lst_cmd.next : pas de pipe, pas de cmd suivante 
	// OU si built-in (comparer le contenu de lst_cmd.cmd a la liste des built-in)
	//
	//dup2 les entree et sorties
	//close
	//execution de la commande sans fork


	//si lst_cmd.next : il y a un pipe
	//dup2 

}



<<<<<<< HEAD:exec/exec.c
	int main(int ac, char **av, char **env)
	{
		t_command lst_cmd;

		char *str[3] = {"echo", "hello", NULL};

		char *str1 = {"infile_1 BOUYA"};
		char *str2 = {"infile_2 Coucou"};
		char *str3 = {"outfile_1 After"};
		char *str4 = {"outfile_2 BYE"};
		
		t_file in1, in2, out1, out2;

		/*lst chainee infile*/
		in1.double_chevron = 1;
		in1.name = ft_strdup(str1);

		in2.double_chevron = 1;
		in2.name = ft_strdup(str2);

		in1.next = &in2;
		in2.next = NULL;

		/*lst chainee outfile*/
		out1.double_chevron = 1;
		out1.name = ft_strdup(str3);

		out2.double_chevron = 2;
		out2.name = ft_strdup(str4);
		out1.next = &out2;
		out2.next = NULL;
		/*link les lst chainee dans le maillon lst_cmd*/

		lst_cmd.infiles = &in1;
		lst_cmd.outfiles = &out1;

		/*attribuer env, lst_cmd et next*/
		lst_cmd.env = env;
		lst_cmd.cmd = str;
		lst_cmd.next = NULL;

		/*okay here we go*/

		exec(cmd);
		
	}
=======
	// int main(int ac, char **av, char **env)
	// {
	// 	t_command cmd;
	// 	cmd.env = env;
	// 	char *str[3] = {"echo", "hello", NULL};
	// 	cmd.cmd = str;
	// 	cmd.next = NULL;

	// 	char *str1 = {"infile_1"};
	// 	char *str2 = {"infile_2"};
	// 	char *str3 = {"outfile_1"};
	// 	char *str4 = {"outfile_2"};
		
	// 	t_file in1, in2, out1, out2;
	// 	in1.double_chevron = 1;
	// 	in1.name = ft_strdup(str1);
	// 	in2.double_chevron = 1;
	// 	in2.name = ft_strdup(str2);
	// 	in1.next = &in2;
	// 	cmd.infiles = &in1;
	// 	out1.double_chevron = 1;
	// 	out1.name = ft_strdup(str3);
	// 	out2.double_chevron = 2;
	// 	out2.name = ft_strdup(str4);
	// 	out1.next = &out2;
	// 	cmd.outfiles = &out1;


	// 	(void)ac;
	// 	(void)av;
	// }
>>>>>>> f1d321d4e8dfb6d428e18476bfc121574b49e0a8:srcs/exec/exec.c
