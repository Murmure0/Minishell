#include "../includes/minishell.h"

char	*update_shell_lvl(char *env)
{
	char	*lvl;
	char	*lvl_char;
	
	lvl = ft_substr(env, 6, ft_strlen(env) - 6);
	lvl_char = ft_itoa(ft_atoi(lvl) + 1);
	env = ft_strjoin("SHLVL=", lvl_char);
	free(lvl);
	free(lvl_char);
	if (!env)
		return (NULL);
	return (env);
}

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
			env[i] = update_shell_lvl(env[i]);
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

char 	**add_slash(char **env_paths)
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

void 	free_tab(char **env_paths)
{
	int	i;
	
	i = 0;
	// pq avancer i ici ?
	// while (env_paths[i])
	// 	i++;
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

char	**realloc_env(char **env)
{
	char	**env_cpy;
	int		i;

	i = -1;
	env_cpy = malloc(sizeof(char *) * (arr_len(env) + 1 + 1));
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
	env = malloc(sizeof(char *) * (arr_len(env_cpy) + 2 + 1));
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
	// i = -1;
	// while (env[++i])
	// 	printf("%s\n", env[i]);a
	return (env);
}

char	**add_env_var(char **env, char *var)
{
	int	i;

	i = 0;
	env = realloc_env(env);
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
<<<<<<< HEAD
		if (!ft_strncmp(env[i], str, ft_strlen(str)))
=======
		if (!strncmp(env[i], key, ft_strlen(key)))
>>>>>>> ff7c745ee0529ba1e9d95f67e90667a4d849b73f
		{
			free(env[i]);
			env[i] = ft_strdup(ft_strjoin(key, value));
			if (!env[i])
				return (NULL);
		}
	}
	return (env);
}