/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmasse <vmasse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 11:18:28 by vmasse            #+#    #+#             */
/*   Updated: 2022/03/11 16:45:19 by vmasse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	create_oldpwd(t_shell *sh, int add_old, char *pwd)
{
	char	*tmp;

	tmp = NULL;
	if (!add_old)
	{
		tmp = ft_strjoin("OLDPWD=", pwd);
		if (!tmp)
			return (0);
		sh->env = add_env_var(sh->env, tmp);
		free(tmp);
		if (!sh->env)
			return (0);
	}
	return (1);
}

void	init_update_env_vars(int *i, int *add_old)
{
	*i = -1;
	*add_old = 0;
}

void	free_get_pwd(char **pwd)
{
	free(*pwd);
	*pwd = getcwd(NULL, 0);
}

int	get_pwds_inside(t_shell *s, char **home, char **pwd, int *add_home)
{
	int	i;

	i = -1;
	*add_home = 0;
	while (s->env[++i])
	{
		if (!ft_strncmp(s->env[i], "HOME=", 5))
		{
			*home = ft_strdup(s->env[i]);
			if (!*home)
			{
				free(*pwd);
				return (-1);
			}
			*add_home = 1;
			return (1);
		}
	}
	return (0);
}
