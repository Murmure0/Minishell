/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 19:12:37 by vmasse            #+#    #+#             */
/*   Updated: 2022/03/02 19:02:50 by mberthet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

int	first_export_var_check(char *cmd) //change
{
	int	i;

	if (cmd[0] != '_' && !ft_isalpha(cmd[0]))
	{
		printf("minishell: export: « %s » : not a valid identifier\n", cmd);
		return (0);
	}
	i = 0;
	while (cmd[++i])
	{
		if (cmd[i] != '_' && cmd[i] != '=' && !ft_isalnum(cmd[i]))
		{
			printf("minishell: export: « %s » : not a valid identifier\n", cmd);
			return (0);
		}
	}
	return (1);
}

int	my_export(t_shell *sh, char **cmd)
{
	int		cmd_pos;
	char	*key;
	char	*value;

	cmd_pos = 0;
	while (cmd[++cmd_pos])
	{
		if (!first_export_var_check(cmd[cmd_pos]))
			return (1);
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
