/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmasse <vmasse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 17:24:22 by vmasse            #+#    #+#             */
/*   Updated: 2022/02/25 20:11:21 by vmasse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**realloc_env_cpy_env(char **env_cpy)
{
	char	**env;
	int		i;

	env = malloc(sizeof(char *) * (arr_len(env_cpy) + 3));
	if (!env)
		return (NULL);
	i = -1;
	while (env_cpy[++i])
	{
		env[i] = ft_strdup(env_cpy[i]);
		if (!env[i])
			return (NULL);
		free(env_cpy[i]);
	}
	env[i] = 0;
	env[i + 1] = 0;
	free(env_cpy);
	return (env);
}

char	**realloc_env(char **env)
{
	char	**env_cpy;
	int		i;

	i = -1;
	env_cpy = malloc(sizeof(char *) * (arr_len(env) + 2));
	if (!env_cpy)
		return (NULL);
	while (env[++i])
	{
		env_cpy[i] = ft_strdup(env[i]);
		if (!env_cpy[i])
			return (NULL);
		free(env[i]);
	}
	env_cpy[i] = 0;
	free(env);
	env = realloc_env_cpy_env(env_cpy);
	if (!env)
		return (NULL);
	return (env);
}

char	**add_env_var(char **env, char *var)
{
	int	i;

	i = 0;
	env = realloc_env(env);
	if (!env)
		return (NULL);
	while (env[i])
		i++;
	free(env[i]);
	env[i] = ft_strdup(var);
	if (!env[i])
		return (NULL);
	return (env);
}

char	**update_env_var(char **env, char *key, char *value)
{
	int		i;
	char	*env_key;

	i = -1;
	while (env && env[++i])
	{
		env_key = str_slice(env[i], 0, get_equal(env[i]) + 1);
		if (!env_key)
			return (NULL);
		if (!ft_strcmp(env_key, key))
		{
			free(env[i]);
			env[i] = ft_strjoin(key, value);
			free(env_key);
			if (!env[i])
				return (NULL);
			return (env);
		}
		free(env_key);
	}
	return (env);
}

char	*get_env_var_value(char **env, char *key)
{
	int		i;
	char	*value;
	char	*env_key;

	i = -1;
	value = NULL;
	while (env && env[++i])
	{
		env_key = str_slice(env[i], 0, get_equal(env[i]));
		if (!env_key)
			return (NULL);
		if (!ft_strcmp(env_key, key))
		{
			value = ft_substr(env[i], ft_strlen(key) + 1, ft_strlen(env[i]));
			if (!value)
			{
				free(env_key);
				return (NULL);
			}
		}
		free(env_key);
	}
	if (!value)
		value = ft_strdup("");
	return (value);
}
