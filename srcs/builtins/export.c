/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmasse <vmasse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 19:12:37 by vmasse            #+#    #+#             */
/*   Updated: 2022/02/25 19:20:48 by vmasse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*get_var_value(char *cmd)
{
	int	i;

	i = -1;
	while (cmd[++i])
	{
		if (cmd[i] == '=')
			return (str_slice(cmd, i + 1, ft_strlen(cmd)));
	}
	return (NULL);
}

static char	*get_var_key(char *cmd)
{
	int	i;

	i = -1;
	while (cmd[++i])
	{
		if (cmd[i] == '=')
			return (str_slice(cmd, 0, i + 1));
	}
	return (NULL);
}

static int	validate_var(char *key, char *value, char *cmd)
{
	int	i;

	i = -1;
	(void)value;
	if (!ft_strncmp(key, "=", 1))
	{
		printf("minishell: export: « %s » : not a valid identifier\n", cmd);
		return (0);
	}
	while (key && key[++i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '=')
		{
			printf("minishell: export: « %s » : not a valid identifier\n", key);
			return (0);
		}
	}
	return (1);
}

static int	check_has_key(char **env, char *key)
{
	int	i;

	i = -1;
	while (env && env[++i])
	{
		if (!ft_strncmp(env[i], key, ft_strlen(key)))
			return (1);
	}
	return (0);
}

int	my_export(t_shell *sh, char **cmd)
{
	int		cmd_pos;
	char	*key;
	char	*value;

	cmd_pos = 0;
	while (cmd[++cmd_pos])
	{
		key = get_var_key(cmd[cmd_pos]);
		if (!key)
			return (-1);
		value = get_var_value(cmd[cmd_pos]);
		if (!validate_var(key, value, cmd[cmd_pos]))
		{
			free_export(key, value);
			continue ;
		}
		if (check_has_key(sh->env, key))
			sh->env = update_env_var(sh->env, key, value);
		else
			sh->env = add_env_var(sh->env, cmd[cmd_pos]);
		if (!sh->env)
			return (-1);
		free_export(key, value);
	}
	return (0);
}