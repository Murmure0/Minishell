/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmasse <vmasse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 15:47:52 by vmasse            #+#    #+#             */
/*   Updated: 2022/02/23 22:06:20 by vmasse           ###   ########.fr       */
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
	char	*env_key;

	if (!var || contains_equal(var))
		return (-1);
	i = -1;
	while (sh->env[++i])
	{
		env_key = str_slice(sh->env[i], 0, get_equal(sh->env[i]));
		if (!ft_strcmp(env_key, var))
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
