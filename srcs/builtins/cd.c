#include "../../includes/minishell.h"

static int get_pwds(t_shell *s, char **old_pwd, char **pwd, char **home)
{
	int		i;

	i = -1;
	while (s->env[++i])
	{
		if (!ft_strncmp(s->env[i], "OLDPWD", 6))
		{
			*old_pwd = ft_strdup(s->env[i]);
			if (!*old_pwd)
				return (0);
		}
		else if (!ft_strncmp(s->env[i], "PWD", 3))
		{
			*pwd = ft_strdup(s->env[i]);
			if (!*pwd)
				return (0);
		}
		else if (!ft_strncmp(s->env[i], "HOME", 4))
		{
			*home = ft_strdup(s->env[i]);
			if (!*home)
				return (0);
		}
	}
	return (1);
}

// static char	**update_env_absolute(char **env, char *dir, char *pwd, char *home)
// {

// }

static char	**update_env_relative(char **env, char *dir, char *pwd, char *home)
{
	int	i;

	if (!ft_strncmp(dir, "./", 2))
	{
		dir = ft_substr(dir, 2, ft_strlen(dir) - 2);
		if (!dir)
			return (NULL);
	}
	i = -1;
	while (env[++i])
	{
		if (!ft_strncmp(env[i], "OLDPWD", 6) && dir)
		{
			free(env[i]);
			env[i] = ft_strjoin("OLD", ft_strdup(pwd));
			if (!env[i])
				return (NULL);
		}
		else if (!ft_strncmp(env[i], "PWD", 3))
		{
			free(env[i]);
			if (dir)
				env[i] = ft_strjoin(pwd, ft_strjoin("/", dir));
			else
				env[i] = ft_strjoin("PWD", ft_substr(home, 4, ft_strlen(home) - 4));
			if (!env[i])
				return (NULL);
		}
	}
	return (env);
}

int	my_cd(t_shell *shell, char *dir)
{
	char	*old_pwd;
	char	*pwd;
	char	*home;

	if (!get_pwds(shell, &old_pwd, &pwd, &home))
		return (-1);
	if (!ft_strncmp(dir, "~/", 2) || !ft_strncmp(dir, "..", 2) || !ft_strncmp(dir, "/", 1))
	{
		chdir(dir);
		// a completer ...
	}
	else
	{
		if (!dir)
		{
			chdir(home);
			update_env_relative(shell->env, NULL, pwd, home);
		}
		else
		{
			chdir(dir);
			update_env_relative(shell->env, dir, pwd, NULL);
		}
	}
	int i = -1;
	while (shell->env[++i])
		printf("%s\n", shell->env[i]);
	free(old_pwd);
	free(pwd);
	free(home);
	return (0);
}