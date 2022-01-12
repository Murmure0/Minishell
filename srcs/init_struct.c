/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmasse <vmasse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 14:07:58 by mberthet          #+#    #+#             */
/*   Updated: 2022/01/12 15:45:28 by vmasse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    init_struct(t_shell *g_struct, char **env)
{
    g_struct->env = get_env(env);
    g_struct->path = get_env_paths(env);
}