/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmasse <vmasse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 13:32:31 by vmasse            #+#    #+#             */
/*   Updated: 2022/01/12 14:16:09 by vmasse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*find_env_paths(char **envp)
{
	char	*env_paths_line;

	if (!envp)
		return (NULL);
	while (envp && *envp)
	{
		if (!ft_strncmp(*envp, "PATH=", 5))
		{
			env_paths_line = ft_substr(*envp, 5, ft_strlen(*envp) - 5);
			if (!env_paths_line)
				return (NULL);
			return (env_paths_line);
		}
		envp++;
	}
	return (NULL);
}

char	**get_env_paths(char **envp)
{
	char	**env_paths;
	char	*env_paths_line;

	env_paths_line = find_env_paths(envp);
	if (!env_paths_line)
		return (NULL);
	env_paths = ft_split(env_paths_line, ':');
	free(env_paths_line);
	if (!env_paths)
		return (NULL);
	return (env_paths);
}