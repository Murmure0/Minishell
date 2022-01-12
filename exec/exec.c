/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 13:14:07 by mberthet          #+#    #+#             */
/*   Updated: 2022/01/12 16:02:15 by mberthet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


int exec(t_shell g_struct, t_command lst_cmd)
{
	int fd_in;
	int fd_out;
	
	//parcourir la lst_cmd.infile : verification qu'il y a du contenu (erreur); si un fd ne peut pas etre ouvert on quitte
	// o/c chaque infile tant qu'il y a un next;
	//verifier le type de redirection : 
	// si < : on ouvre juste le fichier
	// si << : recuparation here_doc.c en changeant des tas de truc
	//on conserve le fd du dernier dans fd_in;
	while (lst_cmd.infiles->next)
	{
		if (lst_cmd.infiles->double_chevron == 0)
		{
			fd_in = open(lst_cmd.infiles->name, O_RDONLY);
			if (fd_in < 0)
			{
				if (ENOENT)
				{
					write(2, &lst_cmd.infiles->name, ft_strlen(lst_cmd.infiles->name));
					write(2, ": Permission denied", 20);
				}
				else if (EACCES)
				{
					write(2, &lst_cmd.infiles->name, ft_strlen(lst_cmd.infiles->name));
					write(2, ": No such file or directory", 28);
				}
				exit (errno);
			}
		}
	}


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