/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmasse <vmasse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 19:12:37 by vmasse            #+#    #+#             */
/*   Updated: 2022/03/01 17:54:00 by vmasse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_var_value(char *cmd)
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

char	*get_var_key(char *cmd)
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

static int	validate_var(char *key, char *cmd)
{
	int	i;

	i = -1;
	if (!ft_strncmp(key, "=", 1))
	{
		printf("minishell: export: « %s » : not a valid identifier\n", cmd);
		return (0);
	}
	while (key && key[++i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_' && key[i] != '=')
		{
			printf("minishell: export: « %s » : not a valid identifier\n", cmd);
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
	int		i;

	cmd_pos = 0;
	i = -1;
	while (cmd[++cmd_pos])
	{
		if (++i == 0 && cmd[cmd_pos][i] != '_' && !ft_isalpha(cmd[cmd_pos][i]))
		{
			printf("minishell: export: « %s » : not a valid identifier\n", cmd[cmd_pos]);
			return (1);
		}
		while (cmd[cmd_pos][++i])
		{
			if (cmd[cmd_pos][i] != '_' && !ft_isalnum(cmd[cmd_pos][i]))
			{
				printf("minishell: export: « %s » : not a valid identifier\n", cmd[cmd_pos]);
				return (1);
			}
		}
		if (!get_key_value_export(&key, &value, cmd[cmd_pos]))
			return (0);
		if (!validate_var(key, cmd[cmd_pos]))
		{
			free_export(key, value);
			return (1);
		}
		if (check_has_key(sh->env, key))
			sh->env = update_env_var(sh->env, key, value);
		else
			sh->env = add_env_var(sh->env, cmd[cmd_pos]);
		if (!sh->env)
			return (1);
		free_export(key, value);
	}
	return (0);
}
