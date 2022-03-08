/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 15:49:59 by vmasse            #+#    #+#             */
/*   Updated: 2022/03/07 11:05:45 by mberthet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	my_env(t_shell *sh, t_node *first_node)
{
	int	i;

	if (first_node->cmd[1])
	{
		write(2, "env: ", 6);
		write(2, first_node->cmd[1], ft_strlen(first_node->cmd[1]));
		write(2, ": No such file or directory\n", 28);
		return (0);
	}
	if (!sh->env || !sh->env[0])
		return (1);
	i = -1;
	while (sh->env[++i])
	{
		write(1, sh->env[i], ft_strlen(sh->env[i]));
		write(1, "\n", 1);
	}
	return (0);
}
