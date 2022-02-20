/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmasse <vmasse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 15:47:52 by vmasse            #+#    #+#             */
/*   Updated: 2022/02/20 15:48:18 by vmasse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*add_key(char *s)
{
	char	*key;
	int		i;

	i = -1;
	while (s[++i] && s[i] != '=')
		continue ;
	key = str_slice(s, 0, i);
	if (!key)
		return (NULL);
	return (key);
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

static int	case_equal(t_shell *sh, char *var)
{
	int		i;
	char	*key;

	i = -1;
	key = add_key(var);
	if (!key)
		return (-1);
	while (sh->env[++i])
	{
		if (!strncmp(sh->env[i], key, ft_strlen(var)))
		{
			free(sh->env[i]);
			sh->env[i] = NULL;
			free(key);
			return (1);
		}
	}
	free(key);
	return (0);
}

int	my_unset(t_shell *sh, char *var)
{
	int		i;

	i = -1;
	if (!var)
		return (1);
	if (contains_equal(var))
		return (case_equal(sh, var));
	else
	{
		while (sh->env[++i])
		{
			if (!strncmp(sh->env[i], var, ft_strlen(var)))
			{
				free(sh->env[i]);
				sh->env[i] = NULL;
				return (0);
			}
		}
	}
	return (1);
}
