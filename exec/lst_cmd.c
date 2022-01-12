/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 16:24:13 by mberthet          #+#    #+#             */
/*   Updated: 2022/01/12 17:18:27 by mberthet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_file *newfile(int chevron, char *name)
{
	t_file *new;

	new = malloc(sizeof(t_file));
	if (!new)
		return (NULL);
	new->double_chevron = chevron;
	new->name = ft_strdup(name);
	if (!new->name)
		return(NULL); //erreur a gerer cornebidouille
	new->next = NULL;
	return(new);
}

t_file *creat_lst_file(int chevron, char *name)
{
	t_file *first;
	t_file *tmp;

	first = newfile(chevron, name);
	if (!first)
		return (NULL);
	tmp = first;

	while () /* HEY */
	{

		tmp->next = newfile(chevron, name);
		if (!tmp->next)
		{
			ft_lstclear(&tmp);
			return(NULL);
		}
		tmp = tmp->next;
	}
	tmp->next = NULL;
	return(first);
}

t_command *newcmd(t_file *infiles, t_file *outfiles, char **)
{

}

t_command *creat_lst_cmd()
{
	t_command *first;
	t_command *tmp;


}