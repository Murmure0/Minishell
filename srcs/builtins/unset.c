/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 15:47:52 by vmasse            #+#    #+#             */
/*   Updated: 2022/03/07 16:12:11 by mberthet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	update_env_paths(t_shell *sh)
{
	int	i;

	i = -1;
	while (sh->path[++i])
		free(sh->path[i]);
	free(sh->path);
	sh->path = get_env_paths(sh->env);
	if (!sh->path)
		return (-1);
	return (1);
}

static int	shift_vars(t_shell *sh, int i)
{
	while (sh->env[i])
	{
		free(sh->env[i]);
		sh->env[i] = ft_strdup(sh->env[i + 1]);
		if (!sh->env[i])
			return (0);
		i++;
	}
	return (1);
}

int	get_equal(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
		if (s[i] == '=')
			return (i);
	return (-1);
}

int	my_unset(t_shell *sh, char **var)
{
	int		i;
	char	*env_key;

	while (var && *var)
	{
		i = -1;
		while (sh->env[++i])
		{
			env_key = str_slice(sh->env[i], 0, get_equal(sh->env[i]));
			if (!env_key)
				return (1);
			if (!ft_strcmp(env_key, *var))
			{
				free(env_key);
				if (!shift_vars(sh, i) && !update_env_paths(sh))
					return (1);
				break ;
			}
			free(env_key);
		}
		var++;
	}
	return (0);
}
