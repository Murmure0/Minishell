/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmasse <vmasse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 13:14:52 by vmasse            #+#    #+#             */
/*   Updated: 2022/02/10 13:33:50 by vmasse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_parstruct(t_parsing *ps)
{
	int	i;

	i = -1;
	if (ps)
	{
		if (ps->prompt)
			free(ps->prompt);
		if (ps->nodes)
		{
			while (ps->nodes[++i])
				free(ps->nodes[i]);
			free(ps->nodes[i]);
			free(ps->nodes);
		}
	}
}

void	free_shellstruct(t_shell *sh)
{
	int	i;

	i = -1;
	if (sh)
	{
		while (sh->env[++i])
			free(sh->env[i]);
		i = -1;
		while (sh->path[++i])
			free(sh->path[i]);
		free(sh->path[i]);
		free(sh->env);
		free(sh->path);
	}
}

void	free_nodestruct(t_node *n)
{
	int	i;
	int	j;
	int	nodes;

	i = -1;
	nodes = 0;
	if (n)
	{
		nodes = n[0].node_nb;
		while (++i < nodes)
		{
			j = -1;
			if (n[i].cmd)
			{
				while (n[i].cmd[++j])
					free(n[i].cmd[j]);
				free(n[i].cmd[j]);
				free(n[i].cmd);
				free(n[i].infiles);
				free(n[i].outfiles);
			}
		}
		free(n);
	}
}

void	final_free(t_shell *sh, t_parsing *ps, t_node *n)
{
	if (n)
		free_nodestruct(n);
	if (ps)
		free_parstruct(ps);
	if (sh)
		free_shellstruct(sh);
}
