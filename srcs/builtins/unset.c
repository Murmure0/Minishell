/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 15:47:52 by vmasse            #+#    #+#             */
/*   Updated: 2022/02/22 14:19:18 by mberthet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	update_env_paths(t_shell *sh)
{
	int	i;

	i = -1;
	while (sh->path[++i])
		free(sh->path[i]);
	free(sh->path[i]);
	free(sh->path);
	sh->path = get_env_paths(sh->env);
	if (!sh->path)
		return (-1);
	return (1);
}

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
		if (!ft_strncmp(sh->env[i], var, ft_strlen(var)))
		{
			free(sh->env[i]);
			sh->env[i] = NULL;
			if (!update_env_paths(sh))
				return (-1);
			return (1);
		}
	}
	return (0);
}
