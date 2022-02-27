#include "../../includes/minishell.h"

static int get_pwds(t_shell *s, char **pwd, char **home)
{
	int		i;

	i = -1;
	while (s->env[++i])
	{
		if (!ft_strncmp(s->env[i], "PWD", 3))
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

// char	*remove_after_last_slash(char *s)
// {
// 	int		len;
// 	char	*tmp;

// 	len = ft_strlen(s);
// 	while (len-- > 0)
// 	{
// 		if (s[len] == '/')
// 		{
// 			tmp = ft_substr(s, 0, len);
// 			if (!tmp)
// 				return (NULL);
// 			s = ft_strdup(tmp);
// 			free(tmp);
// 			if (!s)
// 				return (NULL);
// 			break ;
// 		}
// 	}
// 	return (s);
// }

static void update_env(char **env, char *pwd, char *old_pwd)
{
	int	i;

	i = -1;
	while (env[++i])
	{
		if (!ft_strncmp(env[i], "OLDPWD", 6))
		{
			free(env[i]);
			env[i] = ft_strjoin("OLD", old_pwd);
			if (!env[i])
				return ;
		}
		else if (!ft_strncmp(env[i], "PWD", 3))
		{	
			free(env[i]);
			env[i] = ft_strjoin("PWD=", pwd);
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

int	ret_free(int ret, char *s1, char *s2, char *s3)
{
	if (s1)
		free(s1);
	if (s2)
		free(s2);
	if (s3)
		free(s3);
	return (ret);
}

int	my_cd(t_shell *shell, char *dir)
{
	char	*old_pwd;
	char	*pwd;
	char	*home;

	if (!get_pwds(shell, &pwd, &home))
		return (ret_free(-1, pwd, NULL, home));
	old_pwd = ft_strdup(pwd);
	if (!old_pwd)
		return (ret_free(-1, pwd, NULL, home));
	if (!dir)
	{
		if (!try_chdir(ft_substr(home, 5, ft_strlen(home) - 5)))
			return (ret_free(-1, pwd, old_pwd, home));
		free(pwd);
		pwd = getcwd(NULL, 0);
		update_env(shell->env, pwd, old_pwd);
	}
	else if (dir)
	{
		if (!try_chdir(dir))
			return (ret_free(-1, pwd, old_pwd, home));
		free(pwd);
		pwd = getcwd(NULL, 0);
		update_env(shell->env, pwd, old_pwd);
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
	// free(old_pwd);
	// free(pwd);
	// free(home);
	return (0);
}