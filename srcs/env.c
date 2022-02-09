#include "../includes/minishell.h"

char	**get_env(char **env)
{
	int		i;
	char	**env_cpy;

	i = -1;
	while (env && env[++i])
		continue ;
	env_cpy = malloc(sizeof(char *) * (i + 1));
	if (!env_cpy)
		return (NULL);
	i = -1;
	while (env && env[++i])
	{
		if (!ft_strncmp(env[i], "SHLVL=", 6))
		{
			env[i] = ft_strdup(ft_strjoin("SHLVL=", ft_itoa(ft_atoi(ft_substr(env[i], 6, ft_strlen(env[i]) - 6)) + 1)));
			if (!env[i])
				return (NULL);			
		}
		env_cpy[i] = ft_strdup(env[i]);
		if (!env_cpy[i])
			return (NULL);
	}
	env_cpy[i] = NULL;
	return (env_cpy);
}

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

char **add_slash(char **env_paths)
{
	char **tab_path;
	int	i;
	int j;

	i = 0;
	while (env_paths[i])
		i++;
	i++;
	tab_path = malloc(sizeof(char *) * i);
	tab_path[i-1] = NULL;
	i = -1;
	while(env_paths[++i])
	{
		j = -1;
		tab_path[i] = malloc(sizeof(**env_paths) * (ft_strlen(env_paths[i]) + 2));
		while (env_paths[i][++j])
		{
			tab_path[i][j] = env_paths[i][j];
		}
		tab_path[i][j] = '/';
		j++;
		tab_path[i][j] = '\0';
	}
	return(tab_path);
}

void free_tab(char **env_paths)
{
	int	i;
	
	i = 0;
	while (env_paths[i])
		i++;
	i = -1;
	while (env_paths[++i])
		free(env_paths[i]);
	free(env_paths);
}

char	**get_env_paths(char **envp)
{
	char	**env_paths;
	char	*env_paths_line;
	char	**tab_path;

	env_paths_line = find_env_paths(envp);
	if (!env_paths_line)
		return (NULL);
	env_paths = ft_split(env_paths_line, ':');
	free(env_paths_line);
	if (!env_paths)
		return (NULL);
	tab_path = add_slash(env_paths);
	free_tab(env_paths);
	return (tab_path);
}
