/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmasse <vmasse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 11:18:28 by vmasse            #+#    #+#             */
/*   Updated: 2022/03/11 11:24:33 by vmasse           ###   ########.fr       */
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
