/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmasse <vmasse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 19:20:27 by vmasse            #+#    #+#             */
/*   Updated: 2022/02/25 20:17:36 by vmasse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_export(char *key, char *value)
{
	free(key);
	free(value);
}

int	get_key_value_export(char **key, char **value, char *cmd)
{
	*key = get_var_key(cmd);
	if (!*key)
		return (0);
	*value = get_var_value(cmd);
	if (!*value)
		return (0);
	return (1);
}
