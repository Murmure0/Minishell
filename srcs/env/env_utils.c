/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmasse <vmasse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 17:24:22 by vmasse            #+#    #+#             */
/*   Updated: 2022/02/23 16:37:32 by vmasse           ###   ########.fr       */
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
	int	i;

	i = -1;
	while (env && env[++i])
	{
		if (!ft_strncmp(env[i], key, ft_strlen(key)))
		{
			free(env[i]);
			env[i] = ft_strdup(ft_strjoin(key, value));
			if (!env[i])
				return (NULL);
		}
	}
	return (env);
}

char	*get_env_var_value(char **env, char *key)
{
	int		i;
	char	*value;

	i = -1;
	value = NULL;
	while (env && env[++i])
	{
		/// !!! A CHANGER 
		if (!ft_strncmp(env[i], key, ft_strlen(key)))
		{
			value = ft_substr(env[i], ft_strlen(key) + 1, ft_strlen(env[i]));
			if (!value)
				return (NULL);
		}
	}
	if (!value)
	{
		value = ft_strdup("");
		if (!value)
			return (NULL);
	}
	return (value);
}
