/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmasse <vmasse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 15:26:20 by vmasse            #+#    #+#             */
/*   Updated: 2022/03/11 16:45:11 by vmasse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	get_pwds(t_shell *s, char **pwd, char **home, char *dir)
{
	int	add_home;
	int	ret;

	*pwd = getcwd(NULL, 0);
	if (!pwd)
		return (0);
	ret = get_pwds_inside(s, home, pwd, &add_home);
	if (ret == -1)
		return (0);
	else if (ret == 1)
		return (1);
	if (!add_home && !dir)
	{
		*home = ft_strdup("");
		write(2, "minishell : cd: HOME not set\n", 29);
		free(*pwd);
		return (0);
	}
	else if (!add_home && dir)
	{
		*home = ft_strdup("");
		if (!*home)
			return (0);
	}
	return (1);
}

static int	update_env(t_shell *sh, char *pwd, char *old_pwd)
{
	int	i;
	int	add_old;

	init_update_env_vars(&i, &add_old);
	while (sh->env[++i])
	{
		if (!ft_strncmp(sh->env[i], "OLDPWD=", 7))
		{
			free(sh->env[i]);
			sh->env[i] = ft_strjoin("OLDPWD=", old_pwd);
			if (!sh->env[i])
				return (0);
			add_old = 1;
		}
		else if (!ft_strncmp(sh->env[i], "PWD=", 4))
		{	
			free(sh->env[i]);
			sh->env[i] = ft_strjoin("PWD=", pwd);
			if (!sh->env[i])
				return (0);
		}
	}
	if (!create_oldpwd(sh, add_old, pwd))
		return (0);
	return (1);
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
		write(2, "minishell : ", 12);
		write(2, tmp, ft_strlen(tmp));
		perror(" ");
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

	if (!get_pwds(shell, &pwd, &home, dir))
		return (1);
	old_pwd = ft_strdup(pwd);
	if (!old_pwd)
		return (ret_free(1, pwd, NULL, home));
	if (!dir || !ft_strcmp("", dir))
	{
		if (!try_chdir(NULL, home))
			return (ret_free(1, pwd, old_pwd, home));
	}
	else
		if (!try_chdir(dir, NULL))
			return (ret_free(1, pwd, old_pwd, home));
	free_get_pwd(&pwd);
	if (!pwd)
		return (ret_free(1, NULL, old_pwd, home));
	if (!update_env(shell, pwd, old_pwd))
		return (ret_free(1, pwd, old_pwd, home));
	if (!ft_strcmp("", home))
		return (ret_free(0, pwd, old_pwd, NULL));
	return (ret_free(0, pwd, old_pwd, home));
}
