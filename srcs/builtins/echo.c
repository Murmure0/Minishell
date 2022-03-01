/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 11:35:18 by mberthet          #+#    #+#             */
/*   Updated: 2022/03/01 13:35:29 by mberthet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	no_newline(char *str, char c)
{
	int	k;

	k = 2;
	while (str && str[k] == c)
		k++;
	if (k == ft_strlen(str))
		return (0);
	else
		return (1);
}

static int	write_n(char **str)
{
	if (!ft_strncmp(str[0], "-n", 2) && !no_newline(str[0], 'n'))
		return (0);
	else if ((!ft_strncmp(str[0], "-n", 2) && no_newline(str[0], 'n'))
		|| ft_strncmp(str[0], "-n", 2))
		write(1, "\n", 1);
	return (0);
}

static void	exec_echo(char **str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str && str[i] && str[i][0] == '-' &&
		(str[i][1] == 'n' || str[i][1] == 'e' || str[i][1] == 'E'))
	{
		if ((str[i][1] == 'n' && !no_newline(str[i], 'n'))
			|| (str[i][1] == 'e' && !no_newline(str[i], 'e'))
			|| (str[i][1] == 'E' && !no_newline(str[i], 'E')))
			i++;
		else
			break ;
	}
	while (str && str[i])
	{
		write(1, str[i], ft_strlen(str[i]));
		if (str[++i] != NULL)
			write(1, " ", 1);
	}
}

int	my_echo(char **str)
{
	if (!str || !*str)
	{
		write(1, "\n", 1);
		return (0);
	}
	exec_echo(str);
	write_n(str);
	return (0);
}
