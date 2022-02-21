#include "../../includes/minishell.h"

static int	ret_err_free(int ret, char *msg, char *s1, char *s2)
{
	if (msg)
		printf("%s\n", msg);
	if (s1)
		free(s1);
	if (s2)
		free(s2);
	return (ret);
}

static int	ret_free_full(int ret, char *s1, char *s2, char *s3)
{
	if (s1)
		free(s1);
	if (s2)
		free(s2);
	if (s3)
		free(s3);
	return (ret);
}

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
				return (ret_err(0, "Fail to malloc oldpwd in get pwds"));
		}
		else if (!ft_strncmp(s->env[i], "PWD", 3))
		{
			*pwd = ft_strdup(s->env[i]);
			if (!*pwd)
				return (ret_err(0, "Fail to malloc pwd in get pwds"));
		}
		else if (!ft_strncmp(s->env[i], "HOME", 4))
		{
			*home = ft_strdup(s->env[i]);
			if (!*home)
				return (ret_err(0, "Fail to malloc home in get pwds"));
		}
	}
	return (1);
}

static void update_env(char **env, char *dir, char *pwd, char *home)
{
	int		i;
	char	*tmp;

	i = -1;
	if (dir && !ft_strncmp(dir, "./", 2))
	{
		while (!ft_strncmp(dir, "./", 2))
		{
			tmp = ft_substr(dir, 2, ft_strlen(dir) - 2);
			if (!tmp)
				return ;
			free(dir);
			dir = ft_strdup(tmp);
			if (!dir)
				return ;
		}
	}
	while (env[++i])
	{
		if (!ft_strncmp(env[i], "OLDPWD", 6))
		{
			free(env[i]);
			tmp = ft_strdup(pwd);
			if (!tmp)
				return ;
			env[i] = ft_strjoin("OLD", tmp);
			free(tmp);
			if (!env[i])
				return ;
		}
		else if (!ft_strncmp(env[i], "PWD", 3))
		{
			free(env[i]);
			if (dir && !ft_strncmp(dir, "/", 1))
				env[i] = ft_strjoin("PWD=", dir);			
			else if (dir)
			{
				tmp = ft_strjoin("/", dir);
				if (!tmp)
					return ;
				env[i] = ft_strjoin(pwd, tmp);
				free(tmp);
			}
			else if (home)
			{
				tmp =  ft_substr(home, 5, ft_strlen(home) - 5);
				if (!tmp)
					return ;
				env[i] = ft_strjoin("PWD=", tmp);
				free(tmp);
			}
			if (!env[i])
				return ;
		}
	}
}

static int	try_chdir(char *dir, int home)
{
	char *h;

	if (home)
	{
		h = ft_substr(dir, 5, ft_strlen(dir) - 5);
		if (!h)
			return (-1);
		if (chdir(h) < 0)
		{
			perror(":");
			free(h);
			return (0);
		}
		free(h);
	}
	else if (chdir(dir) < 0)
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

	// minishell$ cd ./
	// builtin detected
	// PWD=/Users/vmasse//
	// OLDPWD=/Users/vmasse/

	// TO DO 3
	// ..

	// PB : après avoir unset HOME, l'exec crashe
	// => réglé avec le path mais quel est le lien ?

	old_pwd = NULL;
	pwd = NULL;
	home = NULL;
	if (!get_pwds(shell, &old_pwd, &pwd, &home))
		return (ret_free_full(-1, home, old_pwd, pwd));
	if (!dir)
	{
		if (!home)
			return (ret_err_free(-1, HOME_UNSET, old_pwd, pwd));
		else if (!try_chdir(home, 1))
			return (ret_free_full(-1, home, old_pwd, pwd));
		update_env(shell->env, NULL, pwd, home);
	}
	if (dir && (!ft_strncmp(dir, "~/", 2) || !ft_strncmp(dir, "..", 2) || !ft_strncmp(dir, "/", 1)))
	{
		if (!try_chdir(dir, 0))
			return (ret_free_full(-1, home, old_pwd, pwd));
		update_env(shell->env, dir, pwd, NULL);
	}
	else if (dir)
	{
		if (!try_chdir(dir, 0))
			return (ret_free_full(-1, home, old_pwd, pwd));
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