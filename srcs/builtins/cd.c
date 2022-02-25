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

static void update_env(char **env, char *dir, char *pwd, char *home)
{
	int	i;

	i = -1;
	if (dir && !ft_strncmp(dir, "./", 2))
	{
		while (!ft_strncmp(dir, "./", 2))
		{
			dir = ft_substr(dir, 2, ft_strlen(dir) - 2);
			if (!dir)
				return ;
		}
	}
	while (env[++i])
	{
		if (!ft_strncmp(env[i], "OLDPWD", 6))
		{
			free(env[i]);
			env[i] = ft_strjoin("OLD", ft_strdup(pwd));
			if (!env[i])
				return ;
		}
		else if (!ft_strncmp(env[i], "PWD", 3))
		{
			free(env[i]);
			if (dir && !ft_strncmp(dir, "/", 1))
				env[i] = ft_strjoin("PWD=", dir);			
			else if (dir)
				env[i] = ft_strjoin(pwd, ft_strjoin("/", dir));
			else if (home)
				env[i] = ft_strjoin("PWD=", ft_substr(home, 5, ft_strlen(home) - 5));
			if (!env[i])
				return ;
		}
	}
}

static int	try_chdir(char *dir)
{
	if (chdir(dir) < 0)
	{
		perror(":");
		return (0);
	}
	return (1);
}

int	my_cd(t_shell *shell, char *dir)
{
	char	*old_pwd;
	char	*pwd;
	char	*home;

	// TO DO 1
	// checker si le home nest pas set
	// bash: cd: HOME not set

	// TO DO 2
	// minishell$ cd ./
	// builtin detected
	// PWD=/Users/vmasse//
	// OLDPWD=/Users/vmasse/

	// TO DO 3
	// ..

	if (!get_pwds(shell, &old_pwd, &pwd, &home))
		return (1);
	if (!dir)
	{
		if (!try_chdir(ft_substr(home, 5, ft_strlen(home) - 5)))
			return (1);
		update_env(shell->env, NULL, pwd, home);
	}
	if (dir && (!ft_strncmp(dir, "~/", 2) || !ft_strncmp(dir, "..", 2) || !ft_strncmp(dir, "/", 1)))
	{
		if (!try_chdir(dir))
			return (1);
		update_env(shell->env, dir, pwd, NULL);
	}
	else if (dir)
	{
		if (!try_chdir(dir))
			return (1);
		update_env(shell->env, dir, pwd, NULL);
	}
	int i = -1;
	while (shell->env[++i])
	{
		if (!ft_strncmp(shell->env[i], "OLDPWD", 6))
		{
			printf("%s\n", shell->env[i]);
		}
		else if (!ft_strncmp(shell->env[i], "PWD", 3))
		{
			printf("%s\n", shell->env[i]);
		}
	}
	free(old_pwd);
	free(pwd);
	free(home);
	return (0);
}