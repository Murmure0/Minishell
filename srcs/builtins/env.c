/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmasse <vmasse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 15:49:59 by vmasse            #+#    #+#             */
/*   Updated: 2022/02/20 15:58:50 by vmasse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	my_env(t_shell *sh)
{
	int	i;

	i = -1;
	while (sh->env[++i])
	{
		printf("%s\n", sh->env[i]);
	}
	return (0);
}