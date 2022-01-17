#include "../../includes/minishell.h"

char	*ft_strdup(char *src)
{
	char	*string;
	int		src_size;
	int		i;

	if (!src)
		return (NULL);
	i = 0;
	src_size = ft_strlen(src);
	string = malloc(sizeof(char) * (src_size + 1));
	if (!string)
		return (NULL);
	while (i < src_size)
	{
		string[i] = src[i];
		i++;
	}
	string[src_size] = '\0';
	return (string);
}

int	ft_strlen(const char *str)
{
	int	count;

	count = 0;
	if (!str)
		return (0);
	while (str[count] != '\0')
		count++;
	return (count);
}

int find_fd_in(t_command lst_cmd)
{
	int fd_in;

	fd_in = 1;
	while (lst_cmd.infiles)
	{
		if (lst_cmd.infiles->double_chevron == 0)
		{
			fd_in = open(lst_cmd.infiles->name, O_RDONLY);
			printf("nom infile : %s\n", lst_cmd.infiles->name);
			printf("|%d|\n", fd_in);
			if (fd_in < 0)
			{
				write(2, lst_cmd.infiles->name, ft_strlen(lst_cmd.infiles->name));
				perror(": ");
				exit (errno);
			}
			if (lst_cmd.infiles->next)
			{
				printf("close %s\n", lst_cmd.infiles->name);
				close(fd_in);
			}
			lst_cmd.infiles = lst_cmd.infiles->next;
		}
	}
	return (fd_in);
}

int exec(t_command lst_cmd)
{
	int fd_out;
	int n;

	n = find_fd_in(lst_cmd);
	printf("valeur fd_in : %d\n",n);
	//parcourir la lst_cmd.infile : verification qu'il y a du contenu (erreur); si un fd ne peut pas etre ouvert on quitte
	// o/c chaque infile tant qu'il y a un next;
	//verifier le type de redirection : 
	// si < : on ouvre juste le fichier
	// si << : recuparation here_doc.c en changeant des tas de truc
	//on conserve le fd du dernier dans fd_in;
	


	//parcourir la lst_cmd.outfile : 
	// - pas de contenu : s'il y a un lst_cmd.next c'est qu'il y a un pipe, on ecrit le resultat de la cmd dans fds[1]
	//						pas de lst_cmd.next : dup sur stdout
	// - o/c chaque infile tant qu'il y a un next;
	// 	conserver le fd du dernier dans un ft_out


	//verifier s'il y a du contenu dans lst_cmd


	//si pas de lst_cmd.next : pas de pipe, pas de cmd suivante 
	// OU si built-in (comparer le contenu de lst_cmd.cmd a la liste des built-in)
	//
	//dup2 les entree et sorties
	//close
	//execution de la commande sans fork


	//si lst_cmd.next : il y a un pipe
	//dup2 
	return (0);
}



	int main(int ac, char **av, char **env)
	{
		t_command lst_cmd;

		char *str[3] = {"echo", "hello", NULL};

		char *str1 = {"infile_1"};
		char *str2 = {"infile_2"};
		char *str3 = {"outfile_1"};
		char *str4 = {"outfile_2"};
		
		t_file in1, in2, out1, out2;

		//lst chainee infile
		in1.double_chevron = 0;
		in1.name = ft_strdup(str1);

		in2.double_chevron = 0;
		in2.name = ft_strdup(str2);

		in1.next = &in2;
		in2.next = NULL;

		/*lst chainee outfile*/
		out1.double_chevron = 0;
		out1.name = ft_strdup(str3);

		out2.double_chevron = 1;
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

		exec(lst_cmd);
		return (0);
	}
