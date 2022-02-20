/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmasse <vmasse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 15:47:52 by vmasse            #+#    #+#             */
/*   Updated: 2022/02/20 18:51:48 by vmasse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	contains_equal(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (s[i] == '=')
			return (1);
	}
	return (0);
}

int	my_unset(t_shell *sh, char *var)
{
	int		i;

	if (!var || contains_equal(var))
		return (-1);
	i = -1;
	while (sh->env[++i])
	{
		if (!strncmp(sh->env[i], var, ft_strlen(var)))
		{
			free(sh->env[i]);
			sh->env[i] = NULL;
			sh->path = get_env_paths(sh->env);
			if (!sh->path)
				return (-1);
			return (1);
		}
	}
	return (0);
}
