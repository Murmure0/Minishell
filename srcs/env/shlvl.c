/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmasse <vmasse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 17:31:55 by vmasse            #+#    #+#             */
/*   Updated: 2022/02/24 17:36:33 by vmasse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_equal(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (s[i] == '=')
			return (i);
	}
	return (-1);
}

char	*update_shell_lvl(char *env)
{
	char	*lvl;
	char	*lvl_char;

	lvl = ft_substr(env, 6, ft_strlen(env) - 6);
	if (!lvl)
		return (NULL);
	lvl_char = ft_itoa(ft_atoi(lvl) + 1);
	if (!lvl_char)
	{
		free(lvl);
		return (NULL);
	}
	env = ft_strjoin("SHLVL=", lvl_char);
	free(lvl);
	free(lvl_char);
	if (!env)
		return (NULL);
	return (env);
}
