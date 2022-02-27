/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmasse <vmasse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 15:26:20 by vmasse            #+#    #+#             */
/*   Updated: 2022/02/27 18:36:26 by vmasse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	get_pwds(t_shell *s, char **pwd, char **home)
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

static void	update_env(char **env, char *pwd, char *old_pwd)
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

static int	try_chdir(char *dir, char *home)
{
	char	*tmp;

	if (home)
	{
		tmp = ft_substr(home, 5, ft_strlen(home) - 5);
		if (!tmp)
			return (0);
	}
	else
	{
		tmp = ft_strdup(dir);
		if (!tmp)
			return (0);
	}
	if (chdir(tmp) < 0)
	{
		perror(":");
		free(tmp);
		return (0);
	}
	free(tmp);
	return (1);
}

static int	ret_free(int ret, char *s1, char *s2, char *s3)
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
		if (!try_chdir(NULL, home))
			return (ret_free(-1, pwd, old_pwd, home));
	}
	else
	{
		if (!try_chdir(dir, NULL))
			return (ret_free(-1, pwd, old_pwd, home));
	}
	free(pwd);
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (ret_free(-1, NULL, old_pwd, home));
	update_env(shell->env, pwd, old_pwd);
	return (ret_free(0, pwd, old_pwd, home));
}
